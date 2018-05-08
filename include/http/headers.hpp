#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP
#include <map>
#include <string>

namespace http {

// Change to vector<pair<string, string>> if order received matters 2 U.
struct Headers : std::map<std::string, std::string> {
    using std::map<std::string, std::string>::map;
};

std::string to_string(const Headers& headers);

}  // namespace http
#endif  // HTTP_HEADERS_HPP
