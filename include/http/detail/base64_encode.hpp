#ifndef HTTP_DETAIL_BASE64_ENCODE_HPP
#define HTTP_DETAIL_BASE64_ENCODE_HPP
#include <string>
#include <vector>

namespace http {
namespace detail {

std::string base64_encode(const std::string& buffer);

std::string base64_encode(const std::vector<unsigned char>& buffer);

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_BASE64_ENCODE_HPP
