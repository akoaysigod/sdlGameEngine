#include "../include/ge/Node.h"

#include "../include/ge/CameraNode.h"
#include "../include/ge/Scene.h"
#include "../../utils/include/ge/UUID.h"

using namespace ge;

Node::Node(const int &width, const int &height):
  width(width),
  height(height),
  uuid(UUID::make()) {}

SDL_Rect Node::getBounds() {
  SDL_Rect bounds = {getX(), getY(), getWidth(), getHeight()};
  if (auto parent = getParent()) {
    auto pBounds = parent->getBounds();
    bounds.x += pBounds.x;
    bounds.y += pBounds.y;
  }
  else if (auto camera = getCameraNode()) {
    bounds.x -= camera->x;
    bounds.y -= camera->y;
  }
  return bounds;
}

void Node::setAnchorPoint(const double &x, const double &y) {
  anchorX = x;
  anchorY = y;
}

int Node::getX() {
  if (auto camera = getCameraNode()) {
    setXScale(camera->getXScale());
  }
  return x - (anchorX * getWidth());
}

int Node::getY() {
  if (auto camera = getCameraNode()) {
    setYScale(camera->getYScale());
  }
  return y - (anchorY * getHeight());
}

void Node::setX(const int &x) {
  this->x = x;
}

void Node::setY(const int &y) {
  this->y = y;
}

void Node::setXY(const int &x, const int &y) {
  setX(x);
  setY(y);
}

void Node::setXScale(const double &scale) {
  xScale = scale;
}

void Node::setYScale(const double &scale) {
  yScale = scale;
}

void Node::setScale(const double &scale) {
  setXScale(scale);
  setYScale(scale);
}

double Node::getXScale() {
  return xScale;
}

double Node::getYScale() {
  return yScale;
}

int Node::getWidth() {
  return (int)(width * xScale);
}

int Node::getHeight() {
  return (int)(height * yScale);
}

//updateable
void Node::update(double delta) {
  if (action) {
    if (action->completed()) {
      this->action = nullptr;
    }
    else {
      action->run(shared_from_this(), delta);
    }
  }

  for (auto child: children) {
    if (child) {
      child->update(delta);
    }
  }
}

void Node::setAction(std::shared_ptr<Action> action) {
  this->action = std::shared_ptr<Action>(action);
}

bool Node::hasAction() {
  return action != nullptr;
}

// hashable
bool Node::operator==(const Hashable &rhs) const {
  return this->getUUID() == rhs.getUUID();
}

std::string Node::getUUID() const {
  return uuid;
}

void Node::add(std::shared_ptr<Node> node) {
  children.push_back(node);
  node->parent = weak_from_this();
  node->visible = true;
  node->cameraNode = cameraNode;
}

std::shared_ptr<Node> Node::remove(std::shared_ptr<Node> node) {
  auto nodeIt = std::find(children.begin(), children.end(), node);
  if (nodeIt != children.end()) {
    children.erase(nodeIt);
    // i forget if it's safe to call reset on possible empty weak_ptr
    // todo: look that up, this will be empty when it's a CameraNode, seems fine though
    (*nodeIt)->parent.reset();
    (*nodeIt)->visible = false;
    (*nodeIt)->cameraNode.reset();
    return *nodeIt;
  }
  return nullptr;
}

void Node::setScene(std::shared_ptr<Scene> scene) {
  visible = true;
  this->scene = scene;
}

std::shared_ptr<Node> Node::getParent() const {
  if (!parent.expired()) {
    return parent.lock();
  }
  return nullptr;
}

std::shared_ptr<CameraNode> Node::getCameraNode() const {
  if (!cameraNode.expired()) {
    return cameraNode.lock();
  }
  return nullptr;
}

void Node::setCameraNode(std::shared_ptr<CameraNode> cameraNode) {
  this->cameraNode = cameraNode;
}

void Node::removeFromParent() {
  if (parent.expired()) {
    return;
  }
  (parent.lock())->remove(shared_from_this());
}

bool Node::isVisible() {
  return visible;
}
