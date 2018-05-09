#include <http/parse/json_ptree.hpp>

#include <sstream>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace http {
namespace parse {

boost::property_tree::ptree json_ptree(const std::string& json_text) {
    boost::property_tree::ptree root;
    std::stringstream ss{json_text};
    boost::property_tree::read_json(ss, root);
    return root;
}

std::string json_string(const boost::property_tree::ptree& ptree) {
    std::stringstream ss;
    write_json(ss, ptree, true);
    return ss.str();
}

}  // namespace parse
}  // namespace http
