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
  const int x = followNode->getX();
  const int y = followNode->getY();
  auto center = getCenter(x, y);
  setXY(center.x, center.y);
}

void CameraNode::update(double delta) {
  if (followNode) {
    const int x = followNode->getX();
    const int y = followNode->getY();

    /*
float lerp = 0.1f;
Vector3 position = this.getCamera().position;
position.x += (Obj.x - position.x) * lerp * deltaTime;
position.y += (Obj.y - position.y) * lerp * deltaTime;
    */
    auto followCenter = getCenter(x, y);

    //v0 + t * (v1 - v0);
    auto lerp = 0.05;
    auto nx = getX() + lerp * (followCenter.x - getX());
    auto ny = getY() + lerp * (followCenter.y - getY());
    //auto nx = (followCenter.x - getX()) * lerp * (delta / 1000);
    //auto ny = (followCenter.y - getY()) * lerp * (delta / 1000);
    //setXY(getX() + nx, getY() + ny);
    setXY(nx, ny);
  }
}
