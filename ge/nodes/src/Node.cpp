#include "../include/ge/Node.h"

#include "../include/ge/Scene.h"
#include "../../utils/include/ge/UUID.h"

using namespace ge;

Node::Node(): uuid(UUID::make()), children(std::vector<std::shared_ptr<Node>>()) {}

Position Node::getPosition() {
  return {x, y};
}

void Node::setPosition(Position position) {
  x = position.x;
  y = position.y;
}

//updateable
void Node::update(double delta) {
  if (action) {
    if (action->completed()) {
      this->action = nullptr;
    }
    else {
      action->run(this, delta);
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
}

void Node::setScene(Scene *scene) {
  this->scene = std::shared_ptr<Scene>(scene);
}
