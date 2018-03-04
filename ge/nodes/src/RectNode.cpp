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
    return {getX() + px, getY() + py, w, h};
  }
  return {getX(), getY(), w, h};
}

//renderable
void RectNode::render(const std::shared_ptr<Renderer> &renderer) {
  renderer->renderRect(getBounds(), r, g, b, a);

  for (auto child: children) {
    auto renderable = std::dynamic_pointer_cast<Renderable>(child);
    if (renderable) {
      renderable->render(renderer);
    }
  }
}
