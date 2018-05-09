#ifndef HTTP_DETAIL_VERIFY_OKAY_HPP
#define HTTP_DETAIL_VERIFY_OKAY_HPP
#include <http/status_line.hpp>

namespace http {
namespace detail {

// Throws exception if status line is not 200 OK
void verify_okay(const Status_line& status_line);

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_VERIFY_OKAY_HPP
