#include <iostream>
#include <boost/asio/io_service.hpp>
#include "server.h"
#include "menu.h"

int main(int argc, char* argv[])
{
	auto port_num = 0;

	menu::display();

	for (size_t i = 1; i <= argc-1; i++)
	{
		if (argv[i] == "-p")
			port_num = std::stoi(argv[i++]);
	}
	
	try
	{
		io_service io_service;
		server server(io_service, port_num);
		io_service.run();

		std::cout << "Have began listening on port " << port_num << std::endl;
	}
	catch (std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}

	while (true)
	{
	}
	return 0;

}
