#ifndef HTTP_MAKE_TLS_CONNECTION_HPP
#define HTTP_MAKE_TLS_CONNECTION_HPP
#include <memory>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace http {

using TLS_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

std::unique_ptr<TLS_socket> make_tls_connection(
    const std::string& host,
    boost::asio::io_service& io_service);

}  // namespace http
#endif  // HTTP_MAKE_TLS_CONNECTION_HPP
