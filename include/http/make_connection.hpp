#ifndef HTTP_MAKE_CONNECTION_HPP
#define HTTP_MAKE_CONNECTION_HPP
#include <memory>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace http {

std::unique_ptr<boost::asio::ip::tcp::socket> make_connection(
    const std::string& host,
    const std::string& service,
    boost::asio::io_service& io_service);

}  // namespace http
#endif  // HTTP_MAKE_CONNECTION_HPP
