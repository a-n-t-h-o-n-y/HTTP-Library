#ifndef HTTP_DETAIL_GET_STATUS_LINE_HPP
#define HTTP_DETAIL_GET_STATUS_LINE_HPP
#include <istream>
#include <string>

#include <boost/asio/error.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

#include <http/detail/verify_okay.hpp>
#include <http/status_line.hpp>

namespace http {
namespace detail {

template <typename Socket, typename Buffer>
Status_line get_status_line(Socket& socket, Buffer& buffer) {
    Status_line status_line;
    boost::system::error_code ec;
    boost::asio::read_until(socket, buffer, "\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::istream status_stream(&buffer);
    status_stream >> status_line.HTTP_version;
    status_stream >> status_line.status_code;
    std::getline(status_stream, status_line.reason_phrase, '\n');
    if (!status_line.reason_phrase.empty()) {
        status_line.reason_phrase.pop_back();  // remove \r
    }
    detail::verify_okay(status_line);
    return status_line;
}

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_GET_STATUS_LINE_HPP
