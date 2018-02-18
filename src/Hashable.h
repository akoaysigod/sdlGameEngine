#pragma once

#include <string>

namespace ge {
  class Hashable {
  public:
    virtual std::string getUUID() const = 0;
    virtual bool operator==(const Hashable &rhs) const = 0;
  };
}
