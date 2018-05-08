#include <http/detail/url_encode.hpp>

#include <iomanip>
#include <sstream>
#include <string>

namespace {

bool is_unreserved(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') || c == '-' || c == '.' || c == '_' ||
           c == '~';
}

}  // namespace

namespace http {
namespace detail {

std::string url_encode(const std::string& text) {
    std::stringstream ss;
    for (char c : text) {
        if (is_unreserved(c)) {
            ss << c;
        } else {
            ss << '%';
            ss << std::hex << std::uppercase << std::setfill('0')
               << std::setw(2);
            ss << static_cast<int>(c);
            ss << std::nouppercase << std::setw(0);
        }
    }
    return ss.str();
}

}  // namespace detail
}  // namespace http
