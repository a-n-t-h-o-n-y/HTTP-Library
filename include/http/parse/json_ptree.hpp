#ifndef HTTP_PARSE_JSON_PTREE_HPP
#define HTTP_PARSE_JSON_PTREE_HPP
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace http {
namespace parse {

/// Parse given json_text into a boost::ptree.
boost::property_tree::ptree json_ptree(const std::string& json_text);

/// Output formatted json text from ptree.
std::string json_string(const boost::property_tree::ptree& ptree);

}  // namespace parse
}  // namespace http
#endif  // HTTP_PARSE_JSON_PTREE_HPP
