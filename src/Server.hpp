#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

namespace std {
	class exception;
}

class Server {
    
public:
    Server(int port);
    virtual ~Server();

	void run(int maxConnections);
private:
    int socket_fd;
    struct sockaddr_in* sock_addr;
	int port;

    void cleanUp();
	void throwError(std::exception e);
	void sendData(const int& to_fd, const sockaddr_in* to_addr) const;
};



#endif
