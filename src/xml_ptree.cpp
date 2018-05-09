#include <http/parse/xml_ptree.hpp>

#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace http {
namespace parse {

boost::property_tree::ptree xml_ptree(const std::string& xml_text) {
    boost::property_tree::ptree root;
    std::stringstream ss{xml_text};
    boost::property_tree::read_xml(ss, root);
    return root;
}

}  // namespace parse
}  // namespace http
