#include "TCPServer.hpp"

TCPServer::TCPServer() {}

TCPServer::~TCPServer() {
    for (auto& clientSocket : clientSockets) {
        clientSocket.close();
    }
    serverSocket.close();
}

bool TCPServer::start(unsigned short port) {
    if (!serverSocket.create() || !serverSocket.bind(port) || !serverSocket.listen()) {
        return false;
    }
    return true;
}

void TCPServer::handleConnections() {
    while (true) {
        TCPSocket clientSocket;
        if (serverSocket.accept(clientSocket)) {
            clientSockets.push_back(clientSocket);
            // Start a thread to handle communication with the client
            // Alternatively, handle communication in this loop
        }
    }
}