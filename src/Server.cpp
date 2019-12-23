#include "Server.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "ServerError.hpp"

Server::Server(int port, int maxConnections)
{
	auto addressFamily = AF_INET;
	auto serviceType = SOCK_STREAM;
	
	this->port = port;

    socket_fd = socket(addressFamily, serviceType, 0);
    if (socket_fd == -1) {
		cleanUp();
		throw ServerCreateSocketError();
    }

	printf("Created socket (FD #%d)\n", socket_fd);

	sock_addr = new sockaddr_in;
	memset((char*) sock_addr, 0, sizeof(*sock_addr));
	sock_addr->sin_family = addressFamily;
	sock_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	sock_addr->sin_port = htons(port);

	int bindReturnValue = bind(socket_fd, (struct sockaddr *)sock_addr, sizeof(*sock_addr));

	if (bindReturnValue < 0) {
		cleanUp();
		throw ServerBindError();
	}

	printf("Socket was bind on port: %d\n", this->port);

	if (listen(socket_fd, maxConnections) < 0) {
		cleanUp();
		throw ServerListenError();
	}

	printf("Server is listening\n");
}

Server::~Server()
{
	cleanUp();
}

void Server::run()
{

	int incoming_connection_fd;
	sockaddr_in* incoming_sockaddress = new sockaddr_in;
	int addr_len = sizeof(*incoming_sockaddress);
	if ((incoming_connection_fd = accept(socket_fd, (struct sockaddr *)incoming_sockaddress, (socklen_t*)&addr_len)) < 0) {
		cleanUp();
		throw ServerAcceptError();
	}

	printf("Accepted connection from client\n");

	sendData(incoming_connection_fd, incoming_sockaddress);
}

void Server::cleanUp()
{
    if (socket_fd >= 0) {
        close(socket_fd);
		socket_fd = -1;
    }
}

void Server::sendData(const int& to_fd, const sockaddr_in* to_addr) const
{
	std::cout << "Connection from: " << ntohl(to_addr->sin_addr.s_addr) << "\n";
	
	int buffer_size = 4096;
	char* client_message = new char[buffer_size];
	int read_size = 0;

	printf("Client message:\n");
	std::stringstream http_header; 

	std::string http_method;
	std::string path;
	std::string protocol;

	read_size = recv(to_fd, client_message, buffer_size, 0);
	if (read_size > 0) {
		printf("%s", client_message);

		http_header << std::string(client_message);
	} 
	else {
		printf("Client hasn't send any message\n");
		return;
	}

	std::vector<std::string> lines;
	std::string segment;
	while(std::getline(http_header, segment)) {
		lines.push_back(segment);
	}

	try {
		// reading first line
		for (int i = 0; i < 3; ++i) {
			http_method += lines[0].at(i);
		}

		int i = 4;
		while (lines[0].at(i) != ' ') {
			path += lines[0].at(i);
			i += 1;
		}

		i += 1;
		for(; i < lines[0].length(); i++) {
			protocol += lines[0].at(i);
		}

		std::cout << "HTTP Method: " << http_method << "\n";
		std::cout << "Path: " << path << "\n";
		std::cout << "Protocol: " << protocol << "\n\n";
	} catch (std::exception& e) {
		printf("Not a HTTP Request\n");
	}

	char hello[] = "Hello from the server";
	write(to_fd, hello, strlen(hello));

	close(to_fd);
}
