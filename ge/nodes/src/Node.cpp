#include "../include/ge/Node.h"

#include "../include/ge/Scene.h"
#include "../../utils/include/ge/UUID.h"

using namespace ge;

Node::Node(const int &width, const int &height):
  width(width),
  height(height),
  uuid(UUID::make()) {}

SDL_Rect Node::getBounds() {
  return {getX(), getY(), getWidth(), getHeight()};
}

void Node::setAnchorPoint(const double &x, const double &y) {
  anchorX = x;
  anchorY = y;
}

int Node::getX() {
  return x - (anchorX * getWidth());
}

int Node::getY() {
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
    child->update(delta);
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
  node->parent = shared_from_this();
}

std::shared_ptr<Node> Node::remove(std::shared_ptr<Node> node) {
  auto nodeIt = std::find(children.begin(), children.end(), node);
  if (nodeIt != children.end()) {
    children.erase(nodeIt);
    (*nodeIt)->parent.reset();
    return *nodeIt;
  }
  return nullptr;
}

void Node::setScene(std::shared_ptr<Scene> scene) {
  this->scene = scene;
}

std::shared_ptr<Node> Node::getParent() const {
  if (!parent.expired()) {
    return parent.lock();
  }
  return nullptr;
}

void Node::removeFromParent() {
  if (parent.expired()) {
    return;
  }
  (parent.lock())->remove(shared_from_this());
}
