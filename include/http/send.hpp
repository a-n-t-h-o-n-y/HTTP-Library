#ifndef HTTP_SEND_HPP
#define HTTP_SEND_HPP
#include <string>

#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/write.hpp>

// #include <http/http_request.hpp>

namespace http {

/// Helper function to send an HTTP_data object to an endpoint.
// template <typename Protocol>
// void send(const HTTP_data& data,
//           boost::asio::basic_stream_socket<Protocol>& socket) {
//     std::string str{to_string(data)};
//     write(socket, boost::asio::buffer(str));
//     // should call boost::asio::write? with ADL
// }

}  // namespace http
#endif  // HTTP_SEND_HPP
