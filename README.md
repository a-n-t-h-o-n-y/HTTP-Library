### HTTP Library

#### Requesting webpage via http
```cpp
using namespace http;
boost::asio::io_service io_s;
std::string host{"www.google.com"};
auto socket_ptr = http::make_connection(host, "http", io_s);
HTTP_request request = generate::basic_GET_request(host, "/about/");

// Send Request to Server
send(request, *socket_ptr);

// Read Response from the Server
HTTP_response response{read(*socket_ptr)};

std::cout << response.message_body;
socket_ptr->lowest_layer().close();
```

#### Requesting from Twitter REST API via https
```cpp
using namespace http;
boost::asio::io_service io_s;
std::string host{"api.twitter.com"};
auto socket_ptr = make_tls_connection(host, io_s);

// Create Request
auto fav_request =
    generate::basic_GET_request(host, "/1.1/favorites/list.json");
fav_request.request_line.queries["screen_name"] = "BarackObama";
fav_request.request_line.queries["count"] = "1";

// Get Bearer Token from server and insert it into request headers
std::string key{"..."};
std::string secret{"..."};
auto bearer_request = generate::oauth_bearer_token_request(
    key, secret, host, "/oauth2/token", false);
std::string token = oauth::get_bearer_token(bearer_request, *socket_ptr);
oauth::insert_bearer_token(fav_request, token);

// Send Request to Server
send(fav_request, *socket_ptr);

// Read Response from the Server
HTTP_response fav_response{read(*socket_ptr)};

std::string json_response{
    parse::json_string(parse::json_ptree(fav_response.message_body))};

socket_ptr->lowest_layer().close();
```
