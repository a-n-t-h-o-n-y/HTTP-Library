#include <iostream>

#include <boost/asio.hpp>

// #include <http/http_request.hpp>

int main() {
    // Create Socket
    boost::asio::io_service io_s;
    boost::asio::ip::tcp::socket socket{io_s};

    // Connect Socket to Endpoint
    boost::asio::ip::tcp::resolver resolver{io_s};
    boost::asio::ip::tcp::resolver::results_type endpoints{
        // resolver.resolve("localhost", "http")};
        resolver.resolve("www.google.com", "http")};
    boost::asio::connect(socket, endpoints);

    // boost::asio::ip::tcp::endpoint endpoint{boost::asio::ip::tcp::endpoint(
    //     boost::asio::ip::address::from_string("1.1.1.1"), 88)};
    // socket.connect(endpoint);

    socket.close();
    // Create Request
    // HTTP_request request;
    // request.message_body = "";

    // Send Request via Socket
    // http::send();

    // Read Back a Response from the Socket.
    // http::read();

    return 0;
}
