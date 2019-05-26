#include <http/detail/key_value_encode.hpp>

#include <map>
#include <sstream>
#include <string>

#include <http/detail/url_encode.hpp>

namespace http {
namespace detail {

std::string key_value_encode(std::map<std::string, std::string> parameters) {
    std::stringstream ss;
    std::string separator{""};
    for (const auto& kv : parameters) {
        ss << separator << kv.first << '=' << url_encode(kv.second);
        separator = "&";
    }
    return ss.str();
}

}  // namespace detail
}  // namespace http
