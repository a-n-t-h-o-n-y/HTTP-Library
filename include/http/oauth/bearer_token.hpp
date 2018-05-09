#ifndef HTTP_OAUTH_BEARER_TOKEN_HPP
#define HTTP_OAUTH_BEARER_TOKEN_HPP
#include <stdexcept>
#include <string>

#include <boost/asio/basic_stream_socket.hpp>

#include <http/http_request.hpp>
#include <http/http_response.hpp>
#include <http/read.hpp>
#include <http/send.hpp>

namespace http {
namespace oauth {

/// Generate a request for a bearer token.
HTTP_request bearer_token_request(const std::string& consumer_key,
                                  const std::string& consumer_secret,
                                  const std::string& host,
                                  const std::string& URI = "/oauth2/token");

/// Inserts the bearer token into the request's header.
void insert_bearer_token(HTTP_request& request,
                         const std::string& bearer_token);

/// Helper method that sends the request and parses the response for the token.
template <typename Socket>
std::string get_bearer_token(const HTTP_request& bearer_token_request,
                             Socket& socket) {
    http::send(bearer_token_request, socket);
    HTTP_response bearer_response = http::read(socket);
    if (bearer_response.messages["token_type"] != "bearer") {
        std::cout << to_string(bearer_response) << std::endl;
        throw std::runtime_error("Invalid bearer token type");
    }
    return bearer_response.headers["access_token"];
}

}  // namespace oauth
}  // namespace http
#endif  // HTTP_OAUTH_BEARER_TOKEN_HPP
