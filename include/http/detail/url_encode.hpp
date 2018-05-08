#ifndef HTTP_DETAIL_URL_ENCODE_HPP
#define HTTP_DETAIL_URL_ENCODE_HPP
#include <string>

namespace http {
namespace detail {

std::string url_encode(const std::string& text);

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_URL_ENCODE_HPP
