#include <http/request_line.hpp>

#include <sstream>
#include <string>

#include <http/detail/key_value_encode.hpp>

namespace http {

std::string to_string(const Request_line& request_line) {
    std::stringstream ss;
    ss << request_line.HTTP_method << ' ' << request_line.URI;
    if (!request_line.queries.empty()) {
        ss << '?';
        ss << detail::key_value_encode(request_line.queries);
    }
    ss << ' ' << request_line.HTTP_version << "\r\n";
    return ss.str();
}

}  // namespace http
