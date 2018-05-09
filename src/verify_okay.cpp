#include <http/detail/verify_okay.hpp>

#include <sstream>
#include <stdexcept>

#include <http/status_line.hpp>

namespace http {
namespace detail {

// Throws exception if status line is not 200 OK
void verify_okay(const Status_line& status_line) {
    if (status_line.status_code != "200") {
        std::stringstream ss;
        ss << "HTTP error. Reason: ";
        ss << status_line.reason_phrase;
        ss << ". Status Code: ";
        ss << status_line.status_code;
        throw std::runtime_error(ss.str());
    }
}

}  // namespace detail
}  // namespace http
