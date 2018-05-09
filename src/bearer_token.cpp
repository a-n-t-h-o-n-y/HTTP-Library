#include <http/oauth/bearer_token.hpp>

#include <string>

#include <http/http_request.hpp>

namespace http {
namespace oauth {

void insert_bearer_token(HTTP_request& request,
                         const std::string& bearer_token) {
    request.headers["authorization"] = "Bearer " + bearer_token;
}

}  // namespace oauth
}  // namespace http
