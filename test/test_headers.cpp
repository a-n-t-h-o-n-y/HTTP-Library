#include "catch.hpp"

#include <http/headers.hpp>

TEST_CASE("Converting Headers to string", "[Headers]") {
    http::Headers headers;
    headers["Date"] = "Mon, 27 Jul 2009 12:28:53 GMT";
    headers["Server"] = "Apache/2.2.14 (Win32)";
    headers["Last-Modified"] = "Wed, 22 Jul 2009 19:15:56 GMT";
    headers["Content-Length"] = "88";
    headers["Content-Type"] = "text/html";
    headers["Connection"] = "Closed";

    // Headers is a map, sorting inputs.
    std::string as_string{
        "Connection: Closed\r\n"
        "Content-Length: 88\r\n"
        "Content-Type: text/html\r\n"
        "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
        "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
        "Server: Apache/2.2.14 (Win32)\r\n"
        "\r\n"};

    REQUIRE(to_string(headers) == as_string);
}
