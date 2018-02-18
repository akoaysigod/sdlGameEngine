#pragma once

#include "Hashable.h"

#include <string>

namespace ge {
  class Renderer;

  class Renderable: public Hashable {
  public:
    virtual void render(const Renderer &renderer) = 0;
    int zPosition = 0;
  };
}
