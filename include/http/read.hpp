#ifndef HTTP_READ_HPP
#define HTTP_READ_HPP
#include <istream>
#include <string>

#include <boost/asio/streambuf.hpp>

#include <http/detail/get_headers.hpp>
#include <http/detail/get_status_line.hpp>
#include <http/detail/gzip.hpp>
#include <http/detail/read_chunk.hpp>
#include <http/detail/read_length.hpp>
#include <http/detail/to_lowercase.hpp>
#include <http/detail/verify_okay.hpp>
#include <http/http_response.hpp>

namespace http {

// TODO Should be read_response, no overloading on return type.
/// Helper function to read from boost socket type into an HTTP_response.
template <typename Socket>
HTTP_response read(Socket& socket) {
    // Status Line
    HTTP_response response;
    boost::asio::streambuf buffer;
    response.status_line = detail::get_status_line(socket, buffer);

    // Headers
    response.headers = detail::get_headers(socket, buffer);

    // Message Body
    std::string content_length;
    if (response.headers.count("content-length") == 1) {
        content_length = response.headers["content-length"];
    }
    // Exact Length
    if (!content_length.empty()) {
        auto n = std::stoi(content_length);
        response.message_body = detail::read_length(socket, n, buffer);
    } else if (response.headers.count("transfer-encoding") == 1 &&
               response.headers["transfer-encoding"] == "chunked") {
        while (true) {
            std::string chunk{detail::read_chunk(socket, buffer)};
            if (chunk.empty()) {
                break;
            }
            if (chunk != " ") {
                response.message_body.append(chunk);
            }
        }
    }
    if (response.headers.count("content-encoding") == 1 &&
        response.headers["content-encoding"] == "gzip") {
        detail::decompress_gzip(response.message_body);
    }
    return response;
}

/// Async function to read from streaming endpoints. Expects chunked encoding.
/// returns status line and header from initial response.
// HTTP_response async_read(std::function<void(const Message_body&)> callback) {
//     return HTTP_response{};
// }

}  // namespace http

#endif  // HTTP_READ_HPP
