#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include "HttpHeader.hpp"

namespace std {
	class exception;
}

class Server {
    
public:
    Server(int port, int maxConnections);
    virtual ~Server();

	void run();
private:
    int socket_fd;
    struct sockaddr_in* sock_addr;
	int port;

    void cleanUp();
	void sendData(const int& to_fd, const sockaddr_in* to_addr) const;

	void doGet(int to_fd, HttpHeader* httpHeader) const;
};



#endif
