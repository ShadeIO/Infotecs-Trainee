#pragma comment(lib, "Ws2_32.lib")
#include "connect.h"
#include "DynamicLib.h"

#include <WinSock.h>
#include <windows.h>

Connect::Connect(const std::string ip, int port) {
    WSADATA wsaData;

    WORD wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        return;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return;
    }
    else
        printf("The Winsock 2.2 dll was found okay\n");
    isConnected = false;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == SOCKET_ERROR) {
        std::cerr << "Error while creating a socket." << std::endl;
        return;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());;

    if (connect(clientSocket, reinterpret_cast<const sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        closesocket(clientSocket);
        return;
    }
    isConnected = true;
}


void Connect::run() {
    while (true) {
        if (!isConnected) {
            Sleep(1);
            continue;
        }
        receiveData();
        closesocket(clientSocket);
    }
}

void Connect::receiveData() {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        if (recv(clientSocket, buffer, BUFFER_SIZE - 1, 0) <= 0) {
            break;
        }
        std::string data(buffer);
        if (stringLength(data)) {
            std::cout << "Recieved data: " << data << std::endl;
        }
        else {
            std::cout << "Error: the data does not meet the conditions" << std::endl;
        }
    }
}