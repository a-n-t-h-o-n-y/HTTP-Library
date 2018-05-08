#include <string>

#include "catch.hpp"

#include <http/http_response.hpp>

TEST_CASE("Convert HTTP_response to string", "[HTTP_response]") {
    http::HTTP_response response;
    response.status_line.HTTP_version = "HTTP/1.1";
    response.status_line.status_code = "200";
    response.status_line.reason_phrase = "OK";

    response.headers["Date"] = "Mon, 27 Jul 2009 12:28:53 GMT";
    response.headers["Server"] = "Apache/2.2.14 (Win32)";
    response.headers["Last-Modified"] = "Wed, 22 Jul 2009 19:15:56 GMT";
    response.headers["Content-Length"] = "88";
    response.headers["Content-Type"] = "text/html";
    response.headers["Connection"] = "Closed";

    response.message_body =
        "<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>";

    std::string as_string{
        "HTTP/1.1 200 OK\r\n"
        "Connection: Closed\r\n"
        "Content-Length: 88\r\n"
        "Content-Type: text/html\r\n"
        "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
        "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
        "Server: Apache/2.2.14 (Win32)\r\n"
        "\r\n"
        "<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>"};

    REQUIRE(http::to_string(response) == as_string);
}
