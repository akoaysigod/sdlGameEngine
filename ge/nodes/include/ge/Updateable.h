#pragma once

namespace ge {
class Updateable {
public:
  virtual void update(double delta) = 0;
};
}
