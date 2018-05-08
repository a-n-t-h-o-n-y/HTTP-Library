#ifndef HTTP_HTTP_RESPONSE_HPP
#define HTTP_HTTP_RESPONSE_HPP
#include <string>

#include <http/headers.hpp>
#include <http/message_body.hpp>
#include <http/status_line.hpp>

namespace http {

struct HTTP_response {
    Status_line status_line;
    Headers headers;
    Message_body message_body;
};

std::string to_string(const HTTP_response& response);

}  // namespace http
#endif  // HTTP_HTTP_RESPONSE_HPP
