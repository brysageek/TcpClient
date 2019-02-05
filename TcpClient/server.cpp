#include "server.h"

server::server(io_service& io_service, const int port_num): acceptor_(io_service, ip::tcp::endpoint(ip::tcp::v4(), port_num))
{
	this->start_accept();
}


void server::start_accept()
{
	auto connection = connection_handler::create(acceptor_.get_io_service());
	acceptor_.async_accept(connection->get_socket(), boost::bind(&server::handle_accept, this, connection, placeholders::error));
}


void server::handle_accept(boost::shared_ptr<connection_handler> connection,const boost::system::error_code& error)
{
	if (!error)
		connection->start();
	else
		this->start_accept();
}
