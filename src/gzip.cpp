#include <http/detail/gzip.hpp>

#include <string>

#include <boost/iostreams/close.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/write.hpp>

namespace http {
namespace detail {

void decompress_gzip(std::string& gzipped) {
    std::string decoded;
    boost::iostreams::filtering_ostream f_os;
    f_os.push(boost::iostreams::gzip_decompressor());
    f_os.push(boost::iostreams::back_inserter(decoded));

    boost::iostreams::write(f_os, &gzipped[0], gzipped.size());
    boost::iostreams::close(f_os);
    gzipped = decoded;
}

}  // namespace detail
}  // namespace http
