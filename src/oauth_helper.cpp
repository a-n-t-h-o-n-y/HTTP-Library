#include <http/detail/oauth_helper.hpp>

#include <algorithm>
#include <cctype>
#include <ctime>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <openssl/hmac.h>
#include <openssl/rand.h>

#include <boost/algorithm/string.hpp>

#include <http/detail/base64_encode.hpp>
#include <http/detail/url_encode.hpp>
#include <http/http_request.hpp>

namespace http {
namespace detail {

std::string generate_nonce() {
    std::vector<unsigned char> nonce(32, ' ');
    RAND_bytes(nonce.data(), nonce.size());
    std::string nonce_string = base64_encode(nonce);
    // remove all non-alphanumerics
    nonce_string.erase(
        std::remove_if(std::begin(nonce_string), std::end(nonce_string),
                       [](char c) { return !std::isalnum(c); }),
        std::end(nonce_string));
    return nonce_string;
}

std::string generate_timestamp() {
    std::stringstream time_ss;
    time_ss << std::time(nullptr);
    return time_ss.str();
}

std::string generate_hmac_sha1_signature(const std::string& key,
                                         const std::string& message) {
    std::vector<unsigned char> key_buffer(std::begin(key), std::end(key));
    std::vector<unsigned char> message_buffer(std::begin(message),
                                              std::end(message));
    unsigned int length = 20;
    std::vector<unsigned char> result_buffer(length, ' ');

    HMAC_CTX* context = HMAC_CTX_new();
    HMAC_CTX_reset(context);

    // Key
    HMAC_Init_ex(context, static_cast<const void*>(key_buffer.data()),
                 key.length(), EVP_sha1(), nullptr);
    // Message
    HMAC_Update(context, message_buffer.data(), message.length());

    // Resultant Signature
    HMAC_Final(context, result_buffer.data(), &length);

    return base64_encode(result_buffer);
}

std::string generate_signature(const HTTP_request& request,
                               const std::string& consumer_key,
                               const std::string& consumer_secret,
                               const std::string& access_token,
                               const std::string& token_secret,
                               const std::string& version,
                               const std::string& sig_method,
                               const std::string& nonce,
                               const std::string& timestamp,
                               const std::string& service) {
    std::string host;
    if (request.headers.count("host") == 1) {
        host = request.headers.at("host");
    }

    const std::string base_url{service + "://" + host +
                               request.request_line.URI};
    std::vector<std::string> encoded_parameters;
    // QueryString Parameters
    for (const auto& key_value : request.request_line.queries) {
        std::stringstream parameter_ss;
        parameter_ss << url_encode(key_value.first) << '='
                     << url_encode(key_value.second);
        encoded_parameters.push_back(parameter_ss.str());
    }
    // OAuth Parameters
    std::stringstream parameter_ss;
    parameter_ss << url_encode("oauth_consumer_key") << '='
                 << url_encode(consumer_key);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << url_encode("oauth_nonce") << '=' << url_encode(nonce);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << url_encode("oauth_signature_method") << '='
                 << url_encode(sig_method);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << url_encode("oauth_timestamp") << '='
                 << url_encode(timestamp);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << url_encode("oauth_token") << '='
                 << url_encode(access_token);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << url_encode("oauth_version") << '=' << url_encode(version);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    // Message Body Parameters
    for (const auto& key_value : request.messages) {
        std::stringstream parameter_ss;
        parameter_ss << url_encode(key_value.first) << '='
                     << url_encode(key_value.second);
        encoded_parameters.push_back(parameter_ss.str());
    }

    // Build parameters string.
    std::sort(std::begin(encoded_parameters), std::end(encoded_parameters));
    std::stringstream parameters_ss;
    std::string seperator{""};
    for (const auto& key_value : encoded_parameters) {
        parameters_ss << seperator << key_value;
        seperator = "&";
    }
    std::string parameters_string{parameters_ss.str()};

    std::stringstream sig_base_ss;
    sig_base_ss << boost::to_upper_copy(request.request_line.HTTP_method)
                << '&';
    sig_base_ss << url_encode(base_url) << '&';
    sig_base_ss << url_encode(parameters_string);
    const std::string sig_base_string{sig_base_ss.str()};

    const std::string signing_key{url_encode(consumer_secret) + '&' +
                                  url_encode(token_secret)};
    return generate_hmac_sha1_signature(signing_key, sig_base_string);
}

}  // namespace detail
}  // namespace http
