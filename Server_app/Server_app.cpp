#include <iostream>
#include "TCPSocket.hpp"
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock" << std::endl;
        return 1;
    }

    // Create a server socket
    TCPSocket serverSocket;
    if (!serverSocket.create() || !serverSocket.bind(12345) || !serverSocket.listen()) {
        std::cerr << "Error creating server socket" << std::endl;
        WSACleanup();
        return 1;
    }

    std::cout << "Server started. Listening on port 12345..." << std::endl;

    // Accept connections from clients
    TCPSocket clientSocket;
    if (!serverSocket.accept(clientSocket)) {
        std::cerr << "Error accepting client connection" << std::endl;
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected." << std::endl;

    // Close sockets
    serverSocket.close();
    clientSocket.close();

    WSACleanup();

    return 0;
}
