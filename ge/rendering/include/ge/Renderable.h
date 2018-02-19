#pragma once

#include "../../../nodes/include/ge/Hashable.h"

#include <memory>
#include <string>

namespace ge {
  class Renderer;

  class Renderable {
  public:
    virtual void render(const std::shared_ptr<Renderer> &renderer) = 0;
    int zPosition = 0;
  };
}
