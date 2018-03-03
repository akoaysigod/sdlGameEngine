#include "../include/ge/RectNode.h"

#include "../../rendering/include/ge/Renderer.h"

using namespace ge;

RectNode::RectNode(const int &r,
                   const int &g,
                   const int &b,
                   const int &a,
                   const int &w,
                   const int &h): r(r), g(g), b(b), a(a), w(w), h(h) {}

SDL_Rect RectNode::getBounds() {
  if (!parent.expired()) {
    auto parentBounds = this->parent.lock()->getBounds();
    int px = parentBounds.x;
    int py = parentBounds.y;
    return {x + px, y + py, w, h};
  }
  return {x, y, w, h};
}

//renderable
void RectNode::render(const std::shared_ptr<Renderer> &renderer) {
  renderer->renderRect(getBounds(), r, g, b, a);
}
