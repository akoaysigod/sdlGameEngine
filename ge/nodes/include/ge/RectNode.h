#pragma once

#include "Node.h"
#include "../../../rendering/include/ge/Renderable.h"

namespace ge {
  class Renderer;

  class RectNode: public Node, public Renderable {
  public:
    RectNode(const int &r,
             const int &g,
             const int &b,
             const int &a,
             const int &w,
             const int &h);

    //renderable
    void render(const std::shared_ptr<Renderer> &renderer);

  protected:
    const int r;
    const int g;
    const int b;
    const int a;
  };
}
