// WinsockClient.cpp
#include "WinsockClient.h" // Include the header file for WinsockClient class
#include <iostream> // Include for input/output operations

// Constructor: Initialize the client with server IP and port
WinsockClient::WinsockClient(const std::string& serverIP, int port)
    : m_serverIP(serverIP), m_port(port), m_clientSocket(INVALID_SOCKET), m_running(false) {
    std::cout << std::endl << "================ Step 1 : Setup Dll ================" << std::endl;
    // Initialize Winsock
    WSADATA wsaData; // A structure to hold details of the Winsock implementation
    // Initialize Winsock DLL, load it into memory, and check for errors
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error: WSAStartup failed" << std::endl;
        throw std::runtime_error("WSAStartup failed");
    }
    std::cout << "Success: WSAStartup initialized" << std::endl;
}

// Destructor: Clean up resources
WinsockClient::~WinsockClient() {
    std::cout << std::endl << "================ Step 5 : Close Socket ================" << std::endl;
    stop(); // Stop the client
    WSACleanup(); // Clean up Winsock
    std::cout << "Success: Client destroyed and WSA cleaned up" << std::endl;
}

// Start the client
void WinsockClient::start() {
    std::cout << std::endl << "================ Step 2 : Setup Client Socket ================" << std::endl;
    connect(); // Connect to the server
    m_running = true; // Set the running flag to true
    // Start the thread to send messages
    m_sendThread = std::thread(&WinsockClient::sendMessages, this);
    // Start the thread to receive messages
    m_receiveThread = std::thread(&WinsockClient::receiveMessages, this);
    std::cout << "Success: Client started and threads initialized" << std::endl;
}

// Stop the client
void WinsockClient::stop() {
    m_running = false; // Set the running flag to false
    // Join the send and receive threads if they're joinable
    if (m_sendThread.joinable()) m_sendThread.join();
    if (m_receiveThread.joinable()) m_receiveThread.join();
    disconnect(); // Disconnect from the server
    std::cout << "Success: Client stopped and disconnected" << std::endl;
}

// Connect to the server
void WinsockClient::connect() {
    // Create socket
    m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create a TCP socket for IPv4
    if (m_clientSocket == INVALID_SOCKET) {
        std::cerr << "Error: Socket creation failed" << std::endl;
        throw std::runtime_error("Socket creation failed");
    }
    std::cout << "Success: Client socket created" << std::endl;


    std::cout << std::endl << "================ Step 3 : Connect with the server ================" << std::endl;
    sockaddr_in clientService;  // Declare a structure to hold server connection information
    clientService.sin_family = AF_INET; // Set to AF_INET for IPv4
    inet_pton(AF_INET, m_serverIP.c_str(), &clientService.sin_addr.s_addr); // Convert IP address to binary form
    clientService.sin_port = htons(m_port); // Set the port number

    // Connect to server
    if (::connect(m_clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        closesocket(m_clientSocket);
        std::cerr << "Error: Connection to server failed" << std::endl;
        throw std::runtime_error("Connection failed");
    }
    std::cout << "Success: Connected to server." << std::endl;
}

// Disconnect from the server
void WinsockClient::disconnect() {
    closesocket(m_clientSocket); // Close the client socket
    std::cout << "Success: Disconnected from server" << std::endl;
}

// Send messages to the server
void WinsockClient::sendMessages() {
    std::string message;
    std::cout << std::endl << "================ Step 4-A : Chat with the server [Send] ================" << std::endl;
    while (m_running) {
        std::getline(std::cin, message); // Get input from the user
        if (message == "Quit" || message == "quit") {
            m_running = false; // Set running flag to false if user wants to quit
            std::cout << "User requested to quit. Stopping client..." << std::endl;
            break;
        }
       
        if (send(m_clientSocket, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
            std::cerr << "Error: Failed to send message to server " << ". WSA Error: " << WSAGetLastError() << std::endl;
        }
        else {
            std::cout << "Success: Message sent to server " << std::endl;
        }
    }
}

// Receive messages from the server
void WinsockClient::receiveMessages() {
    std::cout << std::endl << "================ Step 4-B : Chat with the server [Receive] ================" << std::endl;
    char buffer[200]; // Buffer for receiving messages
    while (m_running) {
        int bytesReceived = recv(m_clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "Received: " << std::string(buffer, bytesReceived) << std::endl;
        }
        else if (bytesReceived == 0) {
            std::cout << "Server closed the connection." << std::endl;
            m_running = false;
            break;
        }
        else if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Error: recv failed. WSA Error: " << WSAGetLastError() << std::endl;
            m_running = false;
            break;
        }
    }
    std::cout << "Receive message thread ending." << std::endl;
}