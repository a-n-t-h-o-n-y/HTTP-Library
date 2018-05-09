#include <iostream>
#include <stdexcept>

#include <boost/asio.hpp>

#include <http/http_request.hpp>
#include <http/http_response.hpp>
#include <http/read.hpp>
#include <http/send.hpp>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }
    std::string ep{argv[1]};
    std::string resource{argv[2]};

    // Create Socket
    boost::asio::io_service io_s;
    boost::asio::ip::tcp::socket socket{io_s};

    // Connect Socket to Endpoint
    boost::asio::ip::tcp::resolver resolver{io_s};
    boost::asio::ip::tcp::resolver::results_type endpoints{
        resolver.resolve(ep, "http")};
    boost::asio::connect(socket, endpoints);

    // Create Request
    http::HTTP_request request;
    request.request_line.HTTP_method = "GET";
    request.request_line.URI = resource;
    request.request_line.HTTP_version = "HTTP/1.1";

    request.headers["User-Agent"] =
        "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)";
    request.headers["Host"] = ep;
    request.headers["Accept-Language"] = "en-us";

    // Send Request via Socket
    http::send(request, socket);

    // Read Back a Response from the Socket.
    try {
        http::HTTP_response response = http::read(socket);
        std::cout << "Response:\n" << to_string(response) << '\n';
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        std::cout << "REQUEST:\n" << to_string(request) << std::endl;
    }

    // Close Socket
    socket.close();
    return 0;
}
