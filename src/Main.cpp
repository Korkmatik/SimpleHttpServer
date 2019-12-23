#include <iostream>
#include <exception>

#include "Server.hpp"

int main(int argc, char* argv[])
{

	try {
		Server* httpServer = new Server(9002, 10);
		
		while(true) {
			httpServer->run();
		}
	} catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}
