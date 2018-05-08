#ifndef HTTP_REQUEST_LINE_HPP
#define HTTP_REQUEST_LINE_HPP
#include <map>
#include <string>

namespace http {

struct Request_line {
    std::string HTTP_method;
    std::string URI;
    std::map<std::string, std::string> queries;
    std::string HTTP_version;
};

std::string to_string(const Request_line& request_line);

}  // namespace http
#endif  // HTTP_REQUEST_LINE_HPP
