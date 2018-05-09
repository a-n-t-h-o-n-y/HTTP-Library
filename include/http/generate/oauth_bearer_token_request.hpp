#ifndef HTTP_GENERATE_OAUTH_BEARER_TOKEN_REQUEST_HPP
#define HTTP_GENERATE_OAUTH_BEARER_TOKEN_REQUEST_HPP
#include <string>

#include <http/http_request.hpp>

namespace http {
namespace generate {

/// Generate a request for a bearer token.
HTTP_request oauth_bearer_token_request(
    const std::string& consumer_key,
    const std::string& consumer_secret,
    const std::string& host,
    const std::string& URI = "/oauth2/token",
    bool close_connection = true);

}  // namespace generate
}  // namespace http
#endif  // HTTP_GENERATE_OAUTH_BEARER_TOKEN_REQUEST_HPP
