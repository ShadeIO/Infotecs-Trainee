#pragma once
#include <iostream>

class Connect {
    bool isConnected;
    int clientSocket;
    static const int BUFFER_SIZE = 1024;

public:
    Connect(const std::string ip, int port);

    void run();

private:

    void receiveData();
};