#include <http/http_request.hpp>

#include <sstream>
#include <string>

#include <http/detail/key_value_encode.hpp>

namespace http {

std::string to_string(const HTTP_request& request) {
    std::stringstream ss;
    ss << to_string(request.request_line);

    std::string message_body;
    if (!request.messages.empty()) {
        message_body = detail::key_value_encode(request.messages);
    } else {
        message_body = to_string(request.message_body);
    }

    Headers headers_copy{request.headers};
    headers_copy["Content-Length"] = std::to_string(message_body.length());
    ss << to_string(headers_copy);

    ss << message_body;
    return ss.str();
}

}  // namespace http
