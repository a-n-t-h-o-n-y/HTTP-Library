#include <http/detail/key_value_encode.hpp>

#include <map>
#include <sstream>
#include <string>

#include <http/detail/url_encode.hpp>

namespace http {
namespace detail {

std::string key_value_encode(std::map<std::string, std::string> parameters) {
    std::stringstream ss;
    std::string seperator{""};
    for (const auto& kv : parameters) {
        ss << seperator << kv.first << '=' << url_encode(kv.second);
        seperator = "&";
    }
    return ss.str();
}

}  // namespace detail
}  // namespace http
