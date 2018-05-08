#ifndef HTTP_DETAIL_KEY_VALUE_ENCODE_HPP
#define HTTP_DETAIL_KEY_VALUE_ENCODE_HPP
#include <map>
#include <string>

namespace http {
namespace detail {

std::string key_value_encode(std::map<std::string, std::string> parameters);

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_KEY_VALUE_ENCODE_HPP
