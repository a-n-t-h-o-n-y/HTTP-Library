#ifndef HTTP_DETAIL_GZIP_HPP
#define HTTP_DETAIL_GZIP_HPP
#include <string>

namespace http {
namespace detail {

void decompress_gzip(std::string& gzipped);

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_GZIP_HPP
