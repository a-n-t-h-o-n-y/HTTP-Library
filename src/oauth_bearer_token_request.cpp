#include <http/generate/oauth_bearer_token_request.hpp>

#include <string>

#include <http/detail/base64_encode.hpp>
#include <http/detail/url_encode.hpp>
#include <http/generate/basic_post_request.hpp>
#include <http/http_request.hpp>

namespace http {
namespace generate {

HTTP_request oauth_bearer_token_request(const std::string& consumer_key,
                                        const std::string& consumer_secret,
                                        const std::string& host,
                                        const std::string& URI,
                                        bool close_connection) {
    std::string token_credentials{detail::url_encode(consumer_key) + ':' +
                                  detail::url_encode(consumer_secret)};
    token_credentials = detail::base64_encode(token_credentials);
    HTTP_request bearer_request{
        basic_POST_request(host, URI, close_connection)};
    bearer_request.headers["authorization"] = "Basic " + token_credentials;
    bearer_request.messages["grant_type"] = "client_credentials";
    return bearer_request;
}

}  // namespace generate
}  // namespace http
