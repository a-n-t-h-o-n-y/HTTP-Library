#ifndef HTTP_PARSE_JSON_PTREE_HPP
#define HTTP_PARSE_JSON_PTREE_HPP
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace http {
namespace parse {

boost::property_tree::ptree json_ptree(const std::string& json_text);

}  // namespace parse
}  // namespace http
#endif  // HTTP_PARSE_JSON_PTREE_HPP
