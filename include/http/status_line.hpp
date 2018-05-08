#ifndef HTTP_STATUS_LINE_HPP
#define HTTP_STATUS_LINE_HPP
#include <string>

namespace http {

struct Status_line {
    std::string HTTP_version;
    std::string status_code;
    std::string reason_phrase;
};

std::string to_string(const Status_line& status_line);

}  // namespace http
#endif  // HTTP_STATUS_LINE_HPP
