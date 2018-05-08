#include "catch.hpp"

#include <http/message_body.hpp>

TEST_CASE("Convert Message_body to string", "[Message_body]") {
    http::Message_body message_body;
    message_body = "<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>";

    std::string as_string{
        "<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>"};

    REQUIRE(http::to_string(message_body) == as_string);
}
