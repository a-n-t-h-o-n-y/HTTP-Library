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
    boost::property_tree::write_xml(ss, root, true);
    return root;
}

std::string xml_string(const boost::property_tree::ptree& ptree) {
    std::stringstream ss;
    write_xml(ss, ptree, true);
    return ss.str();
}

}  // namespace parse
}  // namespace http
