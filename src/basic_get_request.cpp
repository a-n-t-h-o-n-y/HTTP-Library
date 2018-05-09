#include <http/generate/basic_get_request.hpp>

#include <string>

#include <http/http_request.hpp>

namespace http {
namespace generate {

HTTP_request basic_GET_request(const std::string& host,
                               const std::string& URI,
                               bool close_connection) {
    HTTP_request request;
    request.request_line.HTTP_method = "GET";
    request.request_line.URI = URI;
    request.request_line.HTTP_version = "HTTP/1.1";

    if (close_connection) {
        request.headers["connection"] = "close";
    }
    request.headers["user-agent"] = "Mozilla/5.0";
    request.headers["accept"] = "*/*";
    request.headers["host"] = host;
    request.headers["accept-encoding"] = "gzip";
    return request;
}

}  // namespace generate
}  // namespace http
