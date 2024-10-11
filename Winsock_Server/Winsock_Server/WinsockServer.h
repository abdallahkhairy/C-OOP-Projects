#ifndef WINSOCKSERVER_H
#define WINSOCKSERVER_H

#include <winsock2.h>  // Include Winsock library
#include <ws2tcpip.h>  // Include for additional Winsock functions
#include <thread>      // Include for std::thread
#include <vector>      // Include for std::vector
#include <queue>       // Include for std::queue
#include <mutex>       // Include for std::mutex
#include <string>      // Include for std::string
#include <stdexcept>   // Include for std::runtime_error
#include <chrono>      // Include for std::chrono
#include <iostream>    // Include for std::cout and std::cerr

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

class WinsockServer {
public:
    // Constructor to initialize server with a specific port
    WinsockServer(int port);

    // Destructor to clean up resources
    ~WinsockServer();

    // Start the server (setup, bind, listen, and handle connections)
    void start();

    // Stop the server and clean up sockets/threads
    void stop();

    // Method to send a message to all clients (wrapper around broadcastMessage)
    void sendToAllClients(const std::string& message);

    bool isRunning() const;

private:
    // Listen for incoming client connections
    void listenForConnections();

    // Receive messages from all connected clients
    void receiveMessages();

    // Send messages to all connected clients
    void sendMessages();

    // Broadcast a message to all connected clients
    void broadcastMessage(const std::string& message);

    // Remove a client socket
    void removeClient(SOCKET clientSocket);

    int m_port;                    // Port number for the server
    SOCKET m_serverSocket;         // Server socket
    std::vector<SOCKET> m_clientSockets; // List of client sockets

    bool m_running;                // Server running flag
    std::thread m_listenThread;    // Thread for listening to new connections
    std::thread m_sendThread;      // Thread for sending messages
    std::thread m_receiveThread;   // Thread for receiving messages

    std::mutex m_clientsMutex;     // Mutex for client sockets access
    std::mutex m_queueMutex;       // Mutex for message queue access

    std::queue<std::string> m_messageQueue; // Queue to store messages for broadcasting
};


inline void WinsockServer::sendToAllClients(const std::string& message)
{
    broadcastMessage(message);
}

inline bool WinsockServer::isRunning() const
{
    return m_running;
}


#endif // WINSOCKSERVER_H
