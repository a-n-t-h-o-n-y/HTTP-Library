#ifndef HTTP_PARSE_XML_PTREE_HPP
#define HTTP_PARSE_XML_PTREE_HPP

#include <string>

#include <boost/property_tree/ptree.hpp>

namespace http {
namespace parse {

/// Parse given xml_text into a boost::ptree.
boost::property_tree::ptree xml_ptree(const std::string& xml_text);

/// Output formatted xml text from ptree.
std::string xml_string(const boost::property_tree::ptree& ptree);

}  // namespace parse
}  // namespace http
#endif  // HTTP_PARSE_XML_PTREE_HPP
