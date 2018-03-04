#include "../include/ge/RectNode.h"

#include "../../rendering/include/ge/Renderer.h"

using namespace ge;

RectNode::RectNode(const int &r,
                   const int &g,
                   const int &b,
                   const int &a,
                   const int &w,
                   const int &h):
  Node::Node(w, h),
  r(r), g(g), b(b), a(a) {}

SDL_Rect RectNode::getBounds() {
  if (!parent.expired()) {
    auto parentBounds = this->parent.lock()->getBounds();
    int px = parentBounds.x;
    int py = parentBounds.y;
    return {getX() + px, getY() + py, getWidth(), getHeight()};
  }
  return {getX(), getY(), getWidth(), getHeight()};
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
