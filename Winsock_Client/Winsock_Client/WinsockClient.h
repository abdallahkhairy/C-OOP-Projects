// WinsockClient.h
#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include <atomic>

class WinsockClient {
public:
    WinsockClient(const std::string& serverIP, int port);
    ~WinsockClient();
    void start();
    void stop();
public:
    bool isRunning() const { return m_running; }
private:
    void connect();
    void disconnect();
    void sendMessages();
    void receiveMessages();

    std::string m_serverIP;
    int m_port;
    SOCKET m_clientSocket;
    std::atomic<bool> m_running;
    std::thread m_sendThread;
    std::thread m_receiveThread;
};
