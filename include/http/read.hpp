#ifndef HTTP_READ_HPP
#define HTTP_READ_HPP
#include <iostream>
#include <istream>
#include <string>

#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

#include <http/detail/gzip.hpp>
#include <http/http_response.hpp>

namespace http {

/// Helper function to read from boost::stream_socket type into an HTTP_data.
template <typename Protocol>
HTTP_response read(boost::asio::basic_stream_socket<Protocol>& socket) {
    HTTP_response response;
    boost::asio::streambuf buffer;

    // Status Line
    boost::system::error_code ec;
    boost::asio::read_until(socket, buffer, "\r\n", ec);
    if (ec != 0) {
        throw boost::system::system_error(ec);
    }
    std::istream input_stream(&buffer);
    input_stream >> response.status_line.HTTP_version;
    input_stream >> response.status_line.status_code;
    std::getline(input_stream, response.status_line.reason_phrase, '\r');

    // Headers
    ec.clear();
    boost::asio::read_until(socket, buffer, "\r\n\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::string line, key, value;
    while (std::getline(input_stream, line, '\n')) {
        if (line.size() > 2) {
            line.pop_back();
            std::string::size_type pos = line.find(": ");
            key = std::string(std::begin(line), std::begin(line) + pos);
            value = std::string(std::begin(line) + pos + 2, std::end(line));
            response.headers[key] = value;
        }
    }

    // Message Body
    std::string content_length;
    try {
        content_length = response.headers.at("content-length");
    } catch (...) {
        std::cout << "invalid header" << '\n';
    }
    // Exact Length
    if (!content_length.empty()) {
        auto n = std::stoi(content_length);
        // response.message_body = detail::read_length(*socket_ptr,
        //                          length, buffer_read);
        ec.clear();
        auto read_n = boost::asio::read(socket, buffer,
                                        boost::asio::transfer_exactly(n), ec);
        if (ec && ec != boost::asio::error::eof) {
            throw boost::system::system_error(ec);
        }
        response.message_body.assign(read_n, ' ');
        input_stream.read(&response.message_body[0], read_n);
        // Chunked Response
        // handle below exception at()
    } else if (response.headers.at("transfer-encoding") == "chunked") {
        while (true) {
            // std::string chunk{detail::read_chunk(*socket_ptr, buffer_read)};
            // Read size
            // deadline for timeout operation.
            ec.clear();
            boost::asio::read_until(socket, buffer, "\r\n", ec);
            if (ec && ec != boost::asio::error::eof) {
                throw boost::system::system_error(ec);
            }
            std::string chunk_size_str;
            input_stream >> chunk_size_str;
            if (chunk_size_str.empty()) {
                return response;
            }
            std::string::size_type chunk_size =
                std::stoul(chunk_size_str, nullptr, 16);
            std::string trash(2, ' ');
            input_stream.read(&trash[0], 2);  // remove "/r/n"

            // Read chunk
            ec.clear();
            auto read_n = boost::asio::read(
                socket, buffer, boost::asio::transfer_exactly(chunk_size), ec);
            if (ec && ec != boost::asio::error::eof) {
                throw boost::system::system_error(ec);
            }
            std::string chunk(read_n, ' ');
            input_stream.read(&chunk[0], read_n);

            // Remove last "\r\n"
            ec.clear();
            boost::asio::read(socket, buffer, boost::asio::transfer_exactly(2),
                              ec);
            input_stream.read(&trash[0], 2);  // remove "/r/n"
            if (ec && ec != boost::asio::error::eof) {
                throw boost::system::system_error(ec);
            }
            if (chunk.empty()) {
                break;
            }
            if (chunk != " ") {
                response.message_body.append(chunk);
            }
        }
    }
    // handle exception below
    if (response.headers.at("content-encoding") == "gzip") {
        detail::decompress_gzip(response.message_body);
    }
    return response;
}

/// Async function to read from streaming endpoints. Expects chunked encoding.
/// returns status line and header from initial response.
HTTP_response async_read(std::function<void(const Message_body&)> callback) {
    return HTTP_response{};
}

}  // namespace http

#endif  // HTTP_READ_HPP
