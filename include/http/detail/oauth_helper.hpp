#ifndef HTTP_DETAIL_OAUTH_HELPER_HPP
#define HTTP_DETAIL_OAUTH_HELPER_HPP
#include <string>

#include <http/http_request.hpp>

namespace http {
namespace detail {

std::string generate_nonce();

std::string generate_timestamp();

std::string generate_hmac_sha1_signature(const std::string& key,
                                         const std::string& message);

std::string generate_signature(const HTTP_request& request,
                               const std::string& consumer_key,
                               const std::string& consumer_secret,
                               const std::string& access_token,
                               const std::string& token_secret,
                               const std::string& version,
                               const std::string& sig_method,
                               const std::string& nonce,
                               const std::string& timestamp,
                               const std::string& service);

}  // namespace detail
}  // namespace http
#endif  // HTTP_DETAIL_OAUTH_HELPER_HPP
