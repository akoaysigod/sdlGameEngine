#include <iterator>
#include <string>
#include <sstream>
#include <vector>

namespace string {
  auto split(const std::string &str) {
    std::istringstream iss(str);
    return std::vector<std::string>(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());

  }
}
