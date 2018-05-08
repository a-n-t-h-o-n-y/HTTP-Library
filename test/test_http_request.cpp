#include <string>

#include "catch.hpp"

#include <http/http_request.hpp>

TEST_CASE("Convert HTTP_request to string", "[HTTP_request]") {
    http::HTTP_request request;
    request.request_line.HTTP_method = "POST";
    request.request_line.URI = "/cgi-bin/process.cgi";
    request.request_line.HTTP_version = "HTTP/1.1";
    request.request_line.queries["foo"] = "bar";
    request.request_line.queries["footwo"] = "foobar";

    request.headers["User-Agent"] =
        "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)";
    request.headers["Host"] = "www.tutorialspoint.com";
    request.headers["Content-Type"] = "application/x-www-form-urlencoded";
    request.headers["Accept-Language"] = "en-us";
    request.headers["Accept-Encoding"] = "gzip, deflate";
    request.headers["Connection"] = "Keep-Alive";

    std::string as_string{
        "POST /cgi-bin/process.cgi?foo=bar&footwo=foobar HTTP/1.1\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "Accept-Language: en-us\r\n"
        "Connection: Keep-Alive\r\n"};

    SECTION("With key-value messages") {
        request.messages["licenseID"] = "string";
        request.messages["content"] = "string";
        request.messages["paramsXML"] = "string";

        as_string.append(
            "Content-Length: 48\r\n"
            "Content-Type: application/x-www-form-urlencoded\r\n"
            "Host: www.tutorialspoint.com\r\n"
            "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
            "\r\n");

        as_string.append("content=string&licenseID=string&paramsXML=string");
        REQUIRE(http::to_string(request) == as_string);
    }

    SECTION("With Message Body") {
        request.message_body =
            R"(<?xml version="1.0" encoding="utf-8"?>)"
            "\n"
            R"(<string xmlns="http://clearforest.com/">string</string>)"
            "\n";

        as_string.append(
            "Content-Length: 95\r\n"
            "Content-Type: application/x-www-form-urlencoded\r\n"
            "Host: www.tutorialspoint.com\r\n"
            "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
            "\r\n");
        as_string.append(request.message_body);
        REQUIRE(http::to_string(request) == as_string);
    }
}
