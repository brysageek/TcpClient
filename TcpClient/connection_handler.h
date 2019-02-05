#pragma once
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
class connection_handler : public boost::enable_shared_from_this<connection_handler>
{
private:
	ip::tcp::socket socket_;
	std::string message_;
	enum{max_length=1024};
	char data_[max_length]{};
public:
	explicit connection_handler(io_service& io_service);
	static boost::shared_ptr<connection_handler> create(io_service& io_service);
	void start();
	ip::tcp::socket& get_socket();
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
	~connection_handler() = default;
};

