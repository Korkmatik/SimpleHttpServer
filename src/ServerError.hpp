#ifndef SERVER_ERROR_H
#define SERVER_ERROR_H

#include <exception>

class ServerCreateSocketError : public std::exception
{
    const char* what() const throw()
    {
        return "Could not create server socket";
    }
};

class ServerBindError : public std::exception
{
	const char* what() const throw()
	{
		return "Could not assign a transport address to the socket";
	}
};

class ServerListenError : public std::exception
{
	const char* what() const throw()
	{
		return "Error while listening for incoming connections";
	}
};

class ServerAcceptError : public std::exception
{
	const char* what() const throw()
	{
		return "Error while accepting an incoming connection";
	}
};

#endif
