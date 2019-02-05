#include "connection_handler.h"
#include <iostream>

connection_handler::connection_handler(io_service& io_service): socket_(io_service)
{
}

boost::shared_ptr<connection_handler> connection_handler::create(io_service& io_service)
{
	return boost::make_shared<connection_handler>(io_service);
}

void connection_handler::start()
{
	socket_.async_read_some(buffer(data_, max_length),
	                        boost::bind(&connection_handler::handle_read, shared_from_this(), placeholders::error,
	                                    placeholders::bytes_transferred));

	socket_.async_write_some(buffer(message_, max_length),
	                         boost::bind(&connection_handler::handle_write, shared_from_this(), placeholders::error,
	                                     placeholders::bytes_transferred));
}

ip::tcp::socket& connection_handler::get_socket()
{
	return socket_;
}

void connection_handler::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
	{
		std::cout << data_ << std::endl;
	}
	else
	{
		std::cerr << "error: " << error.message() << std::endl;
		socket_.close();
	}
}

void connection_handler::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
		std::cout << "Server received a message" << std::endl; //todo
	else
	{
		std::cerr << "error: " << error.message() << std::endl;
		socket_.close();
	}
}
