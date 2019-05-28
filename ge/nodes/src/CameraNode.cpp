#include "../include/ge/CameraNode.h"

#include "../../utils/include/ge/Point.h"

using namespace ge;

Point CameraNode::getCenter(const int &x, const int &y) {
  const int centerWidth = getWidth() / 2;
  const int centerHeight = getHeight() / 2;
  return Point(x - centerWidth, y - centerHeight);
}

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

void CameraNode::follow(const std::shared_ptr<Node> &followNode) {
  this->followNode = followNode;
}

void CameraNode::update(double delta) {
  if (followNode) {
    auto node = followNode.value();
    const int x = node->getX();
    const int y = node->getY();

    auto center = getCenter(x, y);

    setXY(center.x, center.y);
  }
}
