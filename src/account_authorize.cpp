#include <http/oauth/account_authorize.hpp>

#include <sstream>
#include <string>

#include <http/detail/oauth_helper.hpp>
#include <http/detail/url_encode.hpp>
#include <http/http_request.hpp>

namespace http {
namespace oauth {

void account_authorize(HTTP_request& request,
                       const std::string& consumer_key,
                       const std::string& consumer_secret,
                       const std::string& access_token,
                       const std::string& token_secret,
                       const std::string& service) {
    // Gather Parameters
    const std::string version = "1.0";
    const std::string sig_method = "HMAC-SHA1";
    const std::string nonce = detail::generate_nonce();
    const std::string timestamp = detail::generate_timestamp();
    const std::string signature = detail::generate_signature(
        request, consumer_key, consumer_secret, access_token, token_secret,
        version, sig_method, nonce, timestamp, service);

    // Build Authorization Header
    std::stringstream oauth_header;
    oauth_header << "OAuth ";
    oauth_header << detail::url_encode("oauth_consumer_key") << "=\""
                 << detail::url_encode(consumer_key) << "\", ";
    oauth_header << detail::url_encode("oauth_nonce") << "=\""
                 << detail::url_encode(nonce) << "\", ";
    oauth_header << detail::url_encode("oauth_signature") << "=\""
                 << detail::url_encode(signature) << "\", ";
    oauth_header << detail::url_encode("oauth_signature_method") << "=\""
                 << detail::url_encode(sig_method) << "\", ";
    oauth_header << detail::url_encode("oauth_timestamp") << "=\""
                 << detail::url_encode(timestamp) << "\", ";
    oauth_header << detail::url_encode("oauth_token") << "=\""
                 << detail::url_encode(access_token) << "\", ";
    oauth_header << detail::url_encode("oauth_version") << "=\""
                 << detail::url_encode(version) << '\"';

    request.headers["Authorization"] = oauth_header.str();
}

}  // namespace oauth
}  // namespace http
