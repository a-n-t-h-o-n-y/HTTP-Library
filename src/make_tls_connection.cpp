#include <http/make_tls_connection.hpp>

#include <memory>

#include <boost/asio/connect.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/rfc2818_verification.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace http {

std::unique_ptr<TLS_socket> make_tls_connection(
    const std::string& host,
    boost::asio::io_service& io_service) {
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    ssl_context.set_default_verify_paths();
    auto socket_ptr = std::make_unique<TLS_socket>(io_service, ssl_context);

    // Connect Socket to Endpoint
    boost::asio::ip::tcp::resolver resolver{io_service};
    boost::asio::ip::tcp::resolver::query query(host, "https");
    auto endpoint_iterator = resolver.resolve(query);

    // Make connection, perform tls handshake.
    boost::asio::connect(socket_ptr->lowest_layer(), endpoint_iterator);
    socket_ptr->set_verify_mode(boost::asio::ssl::verify_peer);
    socket_ptr->set_verify_callback(
        boost::asio::ssl::rfc2818_verification("api.twitter.com"));
    socket_ptr->handshake(
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client);
    return socket_ptr;
}

}  // namespace http
