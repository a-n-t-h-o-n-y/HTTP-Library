#ifndef HTTP_MESSAGE_BODY_HPP
#define HTTP_MESSAGE_BODY_HPP
#include <string>

namespace http {

struct Message_body : std::string {
    using std::string::string;
    using std::string::operator=;
};

std::string to_string(const Message_body& message_body);

}  // namespace http
#endif  // HTTP_MESSAGE_BODY_HPP
