#ifndef HTTP_DETAIL_READ_LENGTH_HPP
#define HTTP_DETAIL_READ_LENGTH_HPP
#include <cstddef>
#include <istream>
#include <stdexcept>
#include <string>

#include <boost/asio/read.hpp>
#include <boost/system/error_code.hpp>

namespace http {
namespace detail {

/// Reads exact length n from socket, returns a string. Accounts for data
/// already held within buffer.
template <typename Socket, typename Buffer>
std::string read_length(Socket& socket, std::size_t n, Buffer& buffer) {
    std::size_t existing_bytes{buffer.size()};
    std::size_t transfer_bytes{existing_bytes > n ? 0 : n - existing_bytes};
    boost::system::error_code ec;
    auto bytes_read = boost::asio::read(
        socket, buffer, boost::asio::transfer_exactly(transfer_bytes), ec);
    bytes_read += existing_bytes;
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    if (n > bytes_read + existing_bytes) {
        n = bytes_read + existing_bytes;
    }
    std::string result(n, ' ');
    std::istream length_stream(&buffer);
    length_stream.read(&result[0], n);
    return result;
}

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_READ_LENGTH_HPP
