#include <http/http_response.hpp>

#include <sstream>
#include <string>

#include <http/headers.hpp>
#include <http/message_body.hpp>
#include <http/status_line.hpp>

namespace http {

std::string to_string(const HTTP_response& response) {
    std::stringstream ss;
    ss << to_string(response.status_line);
    ss << to_string(response.headers);
    ss << to_string(response.message_body);
    return ss.str();
}

}  // namespace http
