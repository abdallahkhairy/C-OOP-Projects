#include "TCPClient.hpp"
#include <iostream>
TCPClient::TCPClient() {}

TCPClient::~TCPClient() {
    clientSocket.close();
}

bool TCPClient::connectToServer(const std::string& ipAddress, unsigned short port) {
    return clientSocket.create() && clientSocket.connect(ipAddress, port);
}

void TCPClient::send(const std::string& message) {
    clientSocket.send(message.c_str(), message.size());
}

void TCPClient::receive() {
    const int bufferSize = 1024;
    char buffer[bufferSize];
    int bytesReceived = clientSocket.receive(buffer, bufferSize - 1);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }
}