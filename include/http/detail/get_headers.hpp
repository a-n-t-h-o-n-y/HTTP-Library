#ifndef HTTP_DETAIL_GET_HEADERS_HPP
#define HTTP_DETAIL_GET_HEADERS_HPP
#include <cstddef>
#include <istream>
#include <string>

#include <boost/asio/error.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

#include <http/detail/to_lowercase.hpp>
#include <http/headers.hpp>

namespace http {
namespace detail {

template <typename Socket, typename Buffer>
Headers get_headers(Socket& socket, Buffer& buffer) {
    boost::system::error_code ec;
    auto bytes_transferred =
        boost::asio::read_until(socket, buffer, "\r\n\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }

    std::string line, key, value;
    std::istream header_stream(&buffer);
    std::size_t bytes_used{0};
    Headers headers;
    while (bytes_used < bytes_transferred &&
           std::getline(header_stream, line, '\n')) {
        const int thrown_out_newline_length{1};
        bytes_used += line.size() + thrown_out_newline_length;
        if (line.size() > 2) {
            line.pop_back();  // remove \r
            auto pos = line.find(": ");
            key = std::string(std::begin(line), std::begin(line) + pos);
            value = std::string(std::begin(line) + pos + 2, std::end(line));
            detail::to_lowercase(key);
            detail::to_lowercase(value);
            headers[key] = value;
        }
    }
    return headers;
}

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_GET_HEADERS_HPP
