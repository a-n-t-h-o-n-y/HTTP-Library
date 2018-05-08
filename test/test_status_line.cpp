#include "catch.hpp"

#include <http/status_line.hpp>

TEST_CASE("Converting Status_line to string", "[Status_line]") {
    http::Status_line status_line;
    status_line.HTTP_version = "HTTP/1.1";
    status_line.status_code = "200";
    status_line.reason_phrase = "OK";

    std::string as_string{"HTTP/1.1 200 OK\r\n"};

    REQUIRE(http::to_string(status_line) == as_string);
}
