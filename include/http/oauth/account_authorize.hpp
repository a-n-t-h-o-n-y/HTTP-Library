#ifndef HTTP_OAUTH_ACCOUNT_AUTHORIZE_HPP
#define HTTP_OAUTH_ACCOUNT_AUTHORIZE_HPP
#include <string>

#include <http/http_request.hpp>

namespace http {
namespace oauth {

void account_authorize(HTTP_request& request,
                       const std::string& consumer_key,
                       const std::string& consumer_secret,
                       const std::string& access_token,
                       const std::string& token_secret,
                       const std::string& service = "https");

}  // namespace oauth
}  // namespace http
#endif  // HTTP_OAUTH_ACCOUNT_AUTHORIZE_HPP
