#include "Node.h"

#include "Scene.h"
#include "UUID.h"

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
  if (action.has_value()) {
    if ((*action)->completed()) {
      this->action = std::nullopt;
    }
    else {
      (*action)->run(this, delta);
    }
  }

  for (auto child: children) {
    child->update(delta);
  }
}

void Node::setAction(std::shared_ptr<Action> action) {
  this->action = std::optional<std::shared_ptr<Action>>(action);
}

bool Node::hasAction() {
  return action.has_value();
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
