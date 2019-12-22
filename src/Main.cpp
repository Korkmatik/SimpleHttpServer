#include <cstdio>
#include <exception>

#include "Server.hpp"

int main(int argc, char* argv[])
{

	try {
		Server* httpServer = new Server();
		httpServer->run(10);
	} catch (std::exception& e) {
		printf("Error: %s\n", e.what());
	}

	return 0;
}
