#pragma once

#include "../../../nodes/include/ge/Hashable.h"

#include <string>

namespace ge {
  class Renderer;

  class Renderable: public Hashable {
  public:
    virtual void render(const std::shared_ptr<Renderer> &renderer) = 0;
    int zPosition = 0;
  };
}
