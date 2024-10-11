#pragma once
#include "TCPSocket.hpp"
class TCPClient {
private:
    TCPSocket clientSocket;

public:
    TCPClient();
    ~TCPClient();

    bool connectToServer(const std::string& ipAddress, unsigned short port);
    void send(const std::string& message);
    void receive();
};


