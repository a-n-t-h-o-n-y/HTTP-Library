#include <http/oauth/bearer_token.hpp>

#include <string>

#include <http/detail/base64_encode.hpp>
#include <http/detail/url_encode.hpp>
#include <http/http_request.hpp>

namespace http {
namespace oauth {

HTTP_request bearer_token_request(const std::string& consumer_key,
                                  const std::string& consumer_secret,
                                  const std::string& host,
                                  const std::string& URI) {
    std::string token_credentials{detail::url_encode(consumer_key) + ':' +
                                  detail::url_encode(consumer_secret)};
    token_credentials = detail::base64_encode(token_credentials);
    HTTP_request bearer_request;

    bearer_request.request_line.HTTP_method = "POST";
    bearer_request.request_line.URI = URI;
    bearer_request.request_line.queries["include_entities"] = "true";
    bearer_request.request_line.HTTP_version = "HTTP/1.1";

    bearer_request.headers["accept"] = "*/*";
    bearer_request.headers["content-type"] =
        "application/x-www-form-urlencoded;charset=UTF-8";
    bearer_request.headers["host"] = host;
    bearer_request.headers["authorization"] = "Basic " + token_credentials;
    bearer_request.headers["accept-encoding"] = "gzip";

    bearer_request.messages["grant_type"] = "client_credentials";
    return bearer_request;
}

void insert_bearer_token(HTTP_request& request,
                         const std::string& bearer_token) {
    request.headers["authorization"] = "Bearer " + bearer_token;
}

}  // namespace oauth
}  // namespace http
