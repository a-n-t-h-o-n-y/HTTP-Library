#ifndef HTTP_HTTP_REQUEST_HPP
#define HTTP_HTTP_REQUEST_HPP
#include <map>
#include <string>

#include <http/headers.hpp>
#include <http/message_body.hpp>
#include <http/request_line.hpp>

namespace http {

using Messages = std::map<std::string, std::string>;

struct HTTP_request {
    Request_line request_line;
    Headers headers;
    Messages messages;
    Message_body message_body;
};

std::string to_string(const HTTP_request& request);

}  // namespace http
#endif  // HTTP_HTTP_REQUEST_HPP
