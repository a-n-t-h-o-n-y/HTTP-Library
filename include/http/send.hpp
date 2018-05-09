#ifndef HTTP_SEND_HPP
#define HTTP_SEND_HPP
#include <string>

#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/write.hpp>

#include <http/http_request.hpp>

namespace http {

/// Helper function to send an HTTP_data object to an endpoint.
template <typename Socket>
void send(const HTTP_request& request, Socket& socket) {
    std::string str{to_string(request)};
    boost::asio::write(socket, boost::asio::buffer(str));
}

// void send_https();

}  // namespace http
#endif  // HTTP_SEND_HPP
