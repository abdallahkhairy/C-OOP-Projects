#include "TCPSocket.hpp"
#include <iostream>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    // Create a client socket
    TCPSocket clientSocket;
    if (!clientSocket.create() || !clientSocket.connect("127.0.0.1", 12345)) {
        std::cerr << "Error creating or connecting to server socket" << std::endl;
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    // Close socket
    clientSocket.close();

    // Cleanup Winsock
    WSACleanup();

    return 0;
}
