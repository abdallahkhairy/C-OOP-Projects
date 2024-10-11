#include "TCPSocket.hpp"
#include <iostream>
#include <cstring>
#include <ws2tcpip.h> 

TCPSocket::TCPSocket() : socketDescriptor(INVALID_SOCKET) {}

TCPSocket::~TCPSocket() {
    close();
}

bool TCPSocket::create() {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return socketDescriptor != INVALID_SOCKET;
}

bool TCPSocket::bind(unsigned short port) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    return ::bind(socketDescriptor, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) != SOCKET_ERROR;
}

bool TCPSocket::listen(int backlog) {
    return ::listen(socketDescriptor, backlog) != SOCKET_ERROR;
}

bool TCPSocket::accept(TCPSocket& clientSocket) {
    sockaddr_in clientAddr;
    int clientAddrLength = sizeof(clientAddr);
    SOCKET clientSocketDescriptor = ::accept(socketDescriptor, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLength);
    if (clientSocketDescriptor != INVALID_SOCKET) {
        clientSocket.socketDescriptor = clientSocketDescriptor;
        return true;
    }
    return false;
}

bool TCPSocket::connect(const std::string& ipAddress, unsigned short port) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr);

    return ::connect(socketDescriptor, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) != SOCKET_ERROR;
}

bool TCPSocket::send(const char* buffer, int length) {
    return ::send(socketDescriptor, buffer, length, 0) != SOCKET_ERROR;
}

int TCPSocket::receive(char* buffer, int length) {
    return ::recv(socketDescriptor, buffer, length, 0);
}

void TCPSocket::close() {
    if (socketDescriptor != INVALID_SOCKET) {
        ::closesocket(socketDescriptor);
        socketDescriptor = INVALID_SOCKET;
    }
}