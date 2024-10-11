#pragma once

#include <string>
#include <winsock2.h>

class TCPSocket
{
private:
    SOCKET socketDescriptor;

public:
    TCPSocket();
    ~TCPSocket();

    bool create();
    bool bind(unsigned short port);
    bool listen(int backlog = 5);
    bool accept(TCPSocket& clientSocket);
    bool connect(const std::string& ipAddress, unsigned short port);
    bool send(const char* buffer, int length);
    int receive(char* buffer, int length);
    void close();
};


