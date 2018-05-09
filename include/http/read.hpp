#ifndef HTTP_READ_HPP
#define HTTP_READ_HPP
#include <iostream>
#include <istream>
#include <string>

// #include <utility/log.hpp>  // temp log

#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

#include <http/detail/gzip.hpp>
#include <http/detail/read_chunk.hpp>
#include <http/detail/to_lowercase.hpp>
#include <http/detail/verify_okay.hpp>
#include <http/http_response.hpp>

namespace http {

// TODO Should be read_response, no overloading on return type.
/// Helper function to read from boost::stream_socket type into an HTTP_data.
template <typename Socket>
HTTP_response read(Socket& socket) {
    // utility::Log log;
    HTTP_response response;
    boost::asio::streambuf buffer;
    // log << "Initial Size of streambuf: " << buffer.size() << '\n';

    // Status Line
    boost::system::error_code ec;
    auto n1 = boost::asio::read_until(socket, buffer, "\r\n", ec);
    if (ec != 0) {
        throw boost::system::system_error(ec);
    }
    // log << "Status Line Read into buffer...\n";
    // log << "Bytes Transfered: " << n1 << '\n';
    // log << "Buffer Size: " << buffer.size() << '\n';
    std::cout << "Status Line Read Length: " << n1 << std::endl;
    std::istream status_stream(&buffer);
    status_stream >> response.status_line.HTTP_version;
    status_stream >> response.status_line.status_code;
    std::getline(status_stream, response.status_line.reason_phrase, '\n');
    if (!response.status_line.reason_phrase.empty()) {
        response.status_line.reason_phrase.pop_back();  // remove \r
    }
    detail::verify_okay(response.status_line);
    std::cout << to_string(response.status_line) << std::endl;
    // log << "Status Line Read Out of Buffer...\n";
    // log << "Buffer Size: " << buffer.size() << '\n';

    // Headers
    ec.clear();
    auto bytes_transfered =
        boost::asio::read_until(socket, buffer, "\r\n\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    // log << "All Headers Read into Buffer...\n";
    // log << "Bytes Transfered: " << bytes_transfered << '\n';
    // log << "Buffer Size: " << buffer.size() << '\n';
    std::cout << "Headers Read Length: " << bytes_transfered << std::endl;

    // READ ENTIRE HEADER
    // std::string all_headers(bytes_transfered, ' ');
    // std::istream header_stream(&buffer);
    // header_stream.read(&all_headers[0], bytes_transfered);
    // std::cout << all_headers.find("\r\n\r\n") << '\n';
    // std::cout << all_headers.size() << std::endl;
    // std::cout << all_headers << std::endl;

    std::string line, key, value;
    std::istream header_stream(&buffer);
    std::size_t bytes_used{0};
    while (bytes_used < bytes_transfered &&
           std::getline(header_stream, line, '\n')) {
        bytes_used += line.size() + 1;  // plus  1 for \n not added to line
        if (line.size() > 2) {
            line.pop_back();  // remove \r
            std::string::size_type pos = line.find(": ");
            key = std::string(std::begin(line), std::begin(line) + pos);
            value = std::string(std::begin(line) + pos + 2, std::end(line));
            detail::to_lowercase(key);
            detail::to_lowercase(value);
            response.headers[key] = value;
        }
    }
    // log << "All Headers Read Out of Buffer...\n";
    // log << "Buffer Size: " << buffer.size() << '\n';

    // Message Body
    // MAYBE remove the difference in the actual transfer rate from the
    // content-length or chunk size? but how do you get the actual transfered?
    // Doesn't seen like a good solution.
    std::string content_length;
    if (response.headers.count("content-length") == 1) {
        content_length = response.headers["content-length"];
    }
    // log.flush();
    // Exact Length
    if (!content_length.empty()) {
        auto n = std::stoi(content_length);
        // read() doesn't account for extra from read_until
        std::size_t existing_bytes{buffer.size()};
        n -= existing_bytes;
        // response.message_body = detail::read_length(*socket_ptr,
        //                          length, buffer_read);
        ec.clear();
        auto read_n = boost::asio::read(socket, buffer,
                                        boost::asio::transfer_exactly(n), ec);
        read_n += existing_bytes;
        if (ec && ec != boost::asio::error::eof) {
            throw boost::system::system_error(ec);
        }
        // log << "Exact Message Body Read into Buffer...\n";
        // log << "Bytes Transfered: " << read_n << '\n';
        // log << "Buffer Size: " << buffer.size() << '\n';
        std::cout << "Exact Length Body Read: " << read_n << std::endl;
        response.message_body.assign(read_n, ' ');
        std::istream length_stream(&buffer);
        length_stream.read(&response.message_body[0], read_n);
        // log << "Exact Message Body Read Out of Buffer...\n";
        // log << "Buffer Size: " << buffer.size() << '\n';
    } else if (response.headers.count("transfer-encoding") == 1 &&
               response.headers["transfer-encoding"] == "chunked") {
        while (true) {
            std::string chunk{detail::read_chunk(socket, buffer)};
            // Read size
            // deadline for timeout operation.
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
