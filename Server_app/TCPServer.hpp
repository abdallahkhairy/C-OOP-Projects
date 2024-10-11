#pragma once
#include "TCPSocket.hpp"
#include <vector>

class TCPServer {
private:
    TCPSocket serverSocket;
    std::vector<TCPSocket> clientSockets;

public:
    TCPServer();
    ~TCPServer();

    bool start(unsigned short port);
    void handleConnections();
};