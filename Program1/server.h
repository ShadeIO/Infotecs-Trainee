#pragma once
#include <iostream>

class Server {

	int serverSocket;

	int clientSocket;

public:

	Server(int port);

	void run();

	void send(std::string num);

	void serverClose();
};
