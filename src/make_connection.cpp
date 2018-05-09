#include <http/make_connection.hpp>

#include <memory>

#include <boost/asio/connect.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace http {

std::unique_ptr<boost::asio::ip::tcp::socket> make_connection(
    const std::string& host,
    const std::string& service,
    boost::asio::io_service& io_service) {
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::results_type endpoints =
        resolver.resolve(host, service);
    auto socket_ptr =
        std::make_unique<boost::asio::ip::tcp::socket>(io_service);
    boost::asio::connect(*socket_ptr, endpoints);

    return socket_ptr;
}

}  // namespace http
