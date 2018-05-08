#include <http/headers.hpp>

#include <sstream>
#include <string>

namespace http {

std::string to_string(const Headers& headers) {
    std::stringstream ss;
    for (const auto& kv : headers) {
        ss << kv.first << ": " << kv.second << "\r\n";
    }
    ss << "\r\n";
    return ss.str();
}

}  // namespace http
