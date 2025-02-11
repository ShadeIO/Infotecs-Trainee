#pragma comment(lib, "Ws2_32.lib")
#include "server.h"
#include <iostream>
#include <thread>
#include <WinSock2.h>

using namespace std;

Server::Server(int port) {
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
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == SOCKET_ERROR)
	{
		std::cerr << "Error while creating a socket." << std::endl;
		return;
	}
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)))
	{
		std::cerr << "Error while binding a socket." << std::endl;
		return;
	}
	listen(serverSocket, 1);
}

void Server::run()
{
	clientSocket = accept(serverSocket, NULL, NULL);
	std::thread reconnectionThread([&]() {
		char buffer[1024];
		while (true)
		{
			if (recv(clientSocket, buffer, 1023, 0) <= 0)
			{
				closesocket(clientSocket);
				clientSocket = accept(serverSocket, NULL, NULL);
			}
		}
		});
	reconnectionThread.detach();
}

void Server::send(string num)
{
	::send(clientSocket, num.c_str(), num.size(), 0);
}

void Server::serverClose() {
	closesocket(serverSocket);
}


