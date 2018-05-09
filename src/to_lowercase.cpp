#include <http/detail/to_lowercase.hpp>

#include <cctype>
#include <string>

namespace http {
namespace detail {

void to_lowercase(std::string& text) {
    for (char& c : text) {
        c = std::tolower(c);
    }
}

}  // namespace detail
}  // namespace http
