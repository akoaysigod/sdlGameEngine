#include "../include/ge/CameraNode.h"

using namespace ge;

void CameraNode::add(std::shared_ptr<Node> node) {
  children.push_back(node);
}

void CameraNode::render(const std::shared_ptr<Renderer> &renderer) {
  for (auto child: children) {
    auto renderable = std::dynamic_pointer_cast<Renderable>(child);
    if (renderable) {
      renderable->render(renderer);
    }
  }
}
