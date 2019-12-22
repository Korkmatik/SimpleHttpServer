#include "Server.hpp"

#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "ServerError.hpp"

Server::Server(int port)
{
	auto addressFamily = AF_INET;
	auto serviceType = SOCK_STREAM;
	
	this->port = port;

    socket_fd = socket(addressFamily, serviceType, 0);
    if (socket_fd == -1) {
		auto error = ServerCreateSocketError();
        throwError(error);
    }

	printf("Created socket (FD #%d)\n", socket_fd);

	sock_addr = new sockaddr_in;
	memset((char*) sock_addr, 0, sizeof(*sock_addr));
	sock_addr->sin_family = addressFamily;
	sock_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	sock_addr->sin_port = htons(port);

	int bindReturnValue = bind(socket_fd, (struct sockaddr *)sock_addr, sizeof(*sock_addr));

	if (bindReturnValue < 0) {
		auto error = ServerBindError();
		throwError(error);
	}

	printf("Socket was bind on port: %d\n", this->port);
}

Server::~Server()
{
	cleanUp();
}

void Server::run(int maxConnections)
{
	if (listen(socket_fd, maxConnections) < 0) {
		auto error = ServerListenError();
		throwError(error);
	}

	printf("Server is listening\n");

	int incoming_connection_fd;
	sockaddr_in* incoming_sockaddress = new sockaddr_in;
	int addr_len = sizeof(*incoming_sockaddress);
	if ((incoming_connection_fd = accept(socket_fd, (struct sockaddr *)incoming_sockaddress, (socklen_t*)&incoming_sockaddress)) < 0) {
		auto error = ServerAcceptError();
		throwError(error);
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

void Server::throwError(std::exception e)
{
	cleanUp();
	throw e;
}

void Server::sendData(const int& to_fd, const sockaddr_in* to_addr) const
{
	char buffer[1024] = {0};

	int valread = read(to_fd, buffer, 1024);
	printf("%s\n", buffer);
	
	if (valread < 0) {
		printf("No bytes are there to read\n");
		return;
	}

	char * hello = "Hello from the server";
	write(to_fd, hello, strlen(hello));

	close(to_fd);
}
