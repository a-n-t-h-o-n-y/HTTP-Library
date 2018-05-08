#include <http/status_line.hpp>

#include <sstream>
#include <string>

namespace http {

std::string to_string(const Status_line& status_line) {
    std::stringstream ss;
    ss << status_line.HTTP_version << ' ' << status_line.status_code << ' '
       << status_line.reason_phrase << "\r\n";
    return ss.str();
}

}  // namespace http
