#ifndef HTTP_DETAIL_READ_CHUNK_HPP
#define HTTP_DETAIL_READ_CHUNK_HPP
#include <cstddef>
#include <istream>
#include <string>

#include <boost/system/error_code.hpp>

#include <http/detail/read_length.hpp>

namespace http {
namespace detail {

template <typename Socket, typename Buffer>
std::string read_chunk(Socket& socket, Buffer& buffer) {
    // Chunk Size
    boost::system::error_code ec;
    boost::asio::read_until(socket, buffer, "\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    } else if (ec == boost::asio::error::eof) {
        return "";
    }
    std::string chunk_size_hex;
    std::istream chunk_stream(&buffer);
    chunk_stream >> chunk_size_hex;
    if (chunk_size_hex.empty()) {
        return "";
    }
    auto chunk_size = std::stoul(chunk_size_hex, nullptr, 16);
    if (chunk_size == 0) {
        return "";
    }
    // Remove CRLF
    std::string crlf(2, ' ');
    chunk_stream.read(&crlf[0], 2);

    // Read Chunk
    std::string chunk{read_length(socket, chunk_size, buffer)};

    // Last CRLF
    std::size_t existing_bytes{buffer.size()};
    std::size_t transfer_bytes{existing_bytes >= 2 ? 0 : 2 - existing_bytes};
    boost::asio::read(socket, buffer,
                      boost::asio::transfer_exactly(transfer_bytes), ec);
    chunk_stream.read(&crlf[0], 2);  // remove "/r/n"
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    return chunk;
}

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_READ_CHUNK_HPP
