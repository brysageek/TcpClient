#pragma once
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "connection_handler.h"

using namespace boost::asio;
class server
{
	ip::tcp::acceptor acceptor_;
	void start_accept();
public:
	explicit server(io_service& io_service, const int port_num);
	void handle_accept(boost::shared_ptr<connection_handler> connection,const boost::system::error_code& error);
	~server()=default;
};

