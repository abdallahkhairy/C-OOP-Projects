// WinsockServer.cpp
#include "WinsockServer.h" // Include the header file for WinsockServer class
#include <iostream> // Include for input/output operations
#include <algorithm> // Include for std::remove

// Constructor: Initialize the server with a specified port
WinsockServer::WinsockServer(int port) : m_port(port), m_serverSocket(INVALID_SOCKET), m_running(false) {
    std::cout << std::endl << "================ Step 1 : Setup Dll ================" << std::endl;
    // Initialize Winsock
    WSADATA wsaData;// A structure to hold details of the Winsock implementation
    // Initialize Winsock DLL, load it into memory, and check for errors
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error: WSAStartup failed" << std::endl;
        throw std::runtime_error("WSAStartup failed");
    }
    std::cout << "Success: WSAStartup initialized" << std::endl;
}

// Destructor: Clean up resources
WinsockServer::~WinsockServer() {
    std::cout << std::endl << "================ Step 7 : Close Socket ================" << std::endl;
    stop(); // Stop the server
    WSACleanup(); // Clean up Winsock
    std::cout << "Success: Server destroyed and WSA cleaned up" << std::endl;
}

// Start the server
void WinsockServer::start() {
    std::cout << std::endl << "================ Step 2 : Setup Server Socket ================" << std::endl;
    // Create a socket for the server
    m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_serverSocket == INVALID_SOCKET) {
        std::cerr << "Error: Socket creation failed" << std::endl;
        throw std::runtime_error("Socket creation failed");
    }
    std::cout << "Success: Server socket created" << std::endl;

    std::cout << std::endl << "================ Step 3 : Bind Socket ================" << std::endl;
    // Set up the sockaddr structure
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(m_port);

    // Bind the socket to the address and port number
    if (bind(m_serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        closesocket(m_serverSocket);
        std::cerr << "Error: Bind failed. WSA Error: " << WSAGetLastError() << std::endl;
        throw std::runtime_error("Bind failed");
    }
    std::cout << "Success: Socket bound to address and port" << std::endl;

    std::cout << std::endl << "================ Step 4 : Start Listen ================" << std::endl;
    // Start listening for client connections
    if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(m_serverSocket);
        std::cerr << "Error: Listen failed. WSA Error: " << WSAGetLastError() << std::endl;
        throw std::runtime_error("Listen failed");
    }
    std::cout << "Success: Server listening for connections" << std::endl;

    m_running = true; // Set the running flag to true
    // Start the thread to listen for connections
    m_listenThread = std::thread(&WinsockServer::listenForConnections, this);
    // Start the thread to send messages
    m_sendThread = std::thread(&WinsockServer::sendMessages, this);
    // Start the thread to receive messages
    m_receiveThread = std::thread(&WinsockServer::receiveMessages, this);
    std::cout << "Success: Server started and threads initialized" << std::endl;
}

// Stop the server
void WinsockServer::stop() {
    m_running = false; // Set the running flag to false to stop all loops
    // Join all threads if they're joinable
    if (m_listenThread.joinable()) m_listenThread.join();
    if (m_sendThread.joinable()) m_sendThread.join();
    if (m_receiveThread.joinable()) m_receiveThread.join();

    std::lock_guard<std::mutex> lock(m_clientsMutex); // Lock the clients mutex to ensure thread-safe access
    // Close all client sockets
    for (SOCKET clientSocket : m_clientSockets) {
        closesocket(clientSocket);
    }
    m_clientSockets.clear(); // Clear the client sockets vector
    closesocket(m_serverSocket); // Close the server socket
    std::cout << "Success: Server stopped and all sockets closed" << std::endl;
}

// Listen for incoming connections
void WinsockServer::listenForConnections() {
    std::cout << std::endl << "================ Step 5 : Accept Connection ================" << std::endl;
    while (m_running) {
        // Accept a client socket
        SOCKET clientSocket = accept(m_serverSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            std::lock_guard<std::mutex> lock(m_clientsMutex); // Lock the clients mutex for thread-safe access
            m_clientSockets.push_back(clientSocket); // Add the client socket to the vector
            std::cout << "Success: New client connected. Total clients: " << m_clientSockets.size() << std::endl;
        }
        else {
            std::cerr << "Error: Failed to accept client connection. WSA Error: " << WSAGetLastError() << std::endl;
        }
    }
}

// Receive messages from all connected clients
void WinsockServer::receiveMessages() {
    std::cout << std::endl << "================ Step 6 : Receive Messages from Clients ================" << std::endl;
    while (m_running) {
        std::vector<SOCKET> clientsCopy;
        {
            std::lock_guard<std::mutex> lock(m_clientsMutex);
            clientsCopy = m_clientSockets; // Create a copy of the client sockets to avoid holding the lock while receiving
        }

        for (SOCKET clientSocket : clientsCopy) {
            char buffer[200]; // Buffer for receiving messages
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                std::string message(buffer, bytesReceived);
                std::cout << "Received from client " << clientSocket << ": " << message << std::endl;
           //     broadcastMessage(message); // Broadcast the received message to all clients
            }
            else if (bytesReceived == 0) {
                std::cout << "Client " << clientSocket << " disconnected gracefully" << std::endl;
                removeClient(clientSocket);
            }
            else {
                int error = WSAGetLastError();
                if (error != WSAEWOULDBLOCK) {
                    std::cerr << "Error: recv failed for client " << clientSocket << " with error: " << error << std::endl;
                    removeClient(clientSocket);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Prevent busy-waiting
    }
}

// Remove a client from the list of connected clients
void WinsockServer::removeClient(SOCKET clientSocket) {
    std::lock_guard<std::mutex> lock(m_clientsMutex);
    m_clientSockets.erase(std::remove(m_clientSockets.begin(), m_clientSockets.end(), clientSocket), m_clientSockets.end());
    closesocket(clientSocket);
    std::cout << "Client " << clientSocket << " removed. Total clients: " << m_clientSockets.size() << std::endl;
}

// Add a message to the broadcast queue
void WinsockServer::broadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(m_queueMutex); // Lock the queue mutex for thread-safe access
    m_messageQueue.push(message); // Add the message to the queue
 //   std::cout << "Success: Message added to broadcast queue" << std::endl;
}

// Send messages to all connected clients
void WinsockServer::sendMessages() {
    while (m_running) {
        std::string message;
        {
            std::lock_guard<std::mutex> lock(m_queueMutex); // Lock the queue mutex for thread-safe access
            if (!m_messageQueue.empty()) {
                message = m_messageQueue.front(); // Get the next message
                m_messageQueue.pop(); // Remove the message from the queue
            }
        }
        if (!message.empty()) {
            std::lock_guard<std::mutex> lock(m_clientsMutex); // Lock the clients mutex for thread-safe access
            // Send the message to all connected clients
            for (SOCKET clientSocket : m_clientSockets) {
                if (send(clientSocket, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
                    std::cerr << "Error: Failed to send message to client " << clientSocket << ". WSA Error: " << WSAGetLastError() << std::endl;
                }
                else {
                    std::cout << "Success: Message sent to client " << clientSocket << std::endl;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Prevent busy-waiting
    }
}