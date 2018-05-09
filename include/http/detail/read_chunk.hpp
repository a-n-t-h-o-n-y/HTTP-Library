#ifndef HTTP_DETAIL_READ_CHUNK_HPP
#define HTTP_DETAIL_READ_CHUNK_HPP
#include <cstddef>
#include <iostream>
#include <string>

namespace http {
namespace detail {

template <typename Protocol>
std::string read_chunk(boost::asio::basic_stream_socket<Protocol>& socket,
                       boost::asio::streambuf& buffer) {
    utility::Log log;
    boost::system::error_code ec;

    auto n2 = boost::asio::read_until(socket, buffer, "\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    } else if (ec == boost::asio::error::eof) {
        std::cout << "end of file reading chunk length" << std::endl;
    }
    log << "Chunk Size Read into Buffer...\n";
    log << "Bytes Transfered: " << n2 << '\n';
    log << "Buffer Size: " << buffer.size() << '\n';
    std::cout << "Chunked Size Read: " << n2 << std::endl;
    std::string chunk_size_str;
    std::istream chunk_stream(&buffer);
    chunk_stream >> chunk_size_str;
    std::cout << "Chunk Size hex: " << chunk_size_str << std::endl;
    if (chunk_size_str.empty()) {
        return "";
    }
    log << "Chunk Size Read Out of Buffer...\n";
    log << "Buffer Size: " << buffer.size() << '\n';
    std::string::size_type chunk_size = std::stoul(chunk_size_str, nullptr, 16);
    std::cout << "Chunk Size: " << chunk_size << std::endl;
    if (chunk_size == 0) {
        return "";
    }
    std::string trash(2, ' ');
    chunk_stream.read(&trash[0], 2);  // remove "/r/n"
    log << "2 Trash Bytes Read Out of Buffer...\n";
    log << "Buffer Size: " << buffer.size() << '\n';

    // Read chunk
    // ec.clear();
    // i = 319 magic number
    if (ec) {
        return "";
    }
    // Amount to actually read calculation
    std::size_t read_size{chunk_size};
    if (buffer.size() > chunk_size) {
        chunk_size = 0;
    } else {
        chunk_size -= buffer.size();
    }

    auto read_n = boost::asio::read(
        socket, buffer, boost::asio::transfer_exactly(chunk_size), ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    } else if (ec == boost::asio::error::eof) {
        std::cout << "End of file reading chunk" << std::endl;
    }
    log << "Chunk Read into Buffer...\n";
    log << "Bytes Transfered: " << read_n << '\n';
    log << "Buffer Size: " << buffer.size() << '\n';
    std::cout << "Chunk_size: " << chunk_size << " transfered: " << read_n
              << std::endl;
    read_n = chunk_size;
    std::string chunk(read_size, ' ');
    chunk_stream.read(&chunk[0], read_size);
    log << "Chunk Read Out of Buffer...\n";
    log << "Buffer Size: " << buffer.size() << '\n';
    std::cout << "Amount Reading from Stream: " << read_n << std::endl;
    // std::cout << "Chunk:\n" << chunk << std::endl;

    // Remove last "\r\n"
    // ec.clear();
    if (ec) {
        return chunk;
    }
    auto n3 =
        boost::asio::read(socket, buffer, boost::asio::transfer_exactly(2), ec);
    log << "2 Trash Bytes Read into Buffer...\n";
    log << "Bytes Transfered: " << n3 << '\n';
    log << "Buffer Size: " << buffer.size() << '\n';
    chunk_stream.read(&trash[0], 2);  // remove "/r/n"
    log << "2 Trash Bytes Read Out of Buffer...\n";
    log << "Buffer Size: " << buffer.size() << '\n';
    std::cout << "Last Chunk CFLR Read Length: " << n3 << std::endl;
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    } else if (ec == boost::asio::error::eof) {
        std::cout << "end of file reading last cflr" << std::endl;
    }
    log.flush();
    return chunk;
}

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_READ_CHUNK_HPP
