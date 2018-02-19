#pragma once

#include <SDL.h>

#include "Node.h"
#include "../../../rendering/include/ge/Renderable.h"

namespace ge {
  class Renderer;

  class RectNode: public Node, public Renderable {
  public:
    RectNode(const int &r,
             const int &g,
             const int &b,
             const int &w,
             const int &h);

    SDL_Rect getBounds();

    //renderable
    void render(const std::shared_ptr<Renderer> &renderer);

  private:
    const int r;
    const int g;
    const int b;
    const int w;
    const int h;
  };
}
