#ifndef HTTP_GENERATE_BASIC_GET_REQUEST_HPP
#define HTTP_GENERATE_BASIC_GET_REQUEST_HPP
#include <string>

#include <http/http_request.hpp>

namespace http {
namespace generate {

HTTP_request basic_GET_request(const std::string& host,
                               const std::string& URI,
                               bool close_connection = true);

}  // namespace generate
}  // namespace http
#endif  // HTTP_GENERATE_BASIC_GET_REQUEST_HPP
