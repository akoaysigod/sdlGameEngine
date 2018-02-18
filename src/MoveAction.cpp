#include "MoveAction.h"

#include "Node.h"
#include <iostream>

using namespace ge;

MoveAction::MoveAction(bool isMoveTo,
                       bool isForever,
                       int x,
                       int y,
                       double duration,
                       std::optional<ActionCompletion> completion):
  Action(isForever, duration, Easing::linear(), completion),
  isMoveTo(isMoveTo),
  x(x),
  y(y) {}

void MoveAction::run(Node *node, double delta) {
  if (isMoveTo) {
    x = x - node->x;
    y = y - node->y;
    isMoveTo = false;
  }

  if (timer == 0.0) {
    sPosX = node->x;
    sPosY = node->y;
  }

  moveBy(node, x, y);

  Action::run(node, delta);
}

void MoveAction::moveBy(Node *node, int x, int y) {
  auto time = pointAtTime();

  node->x = sPosX + (x * time);
  node->y = sPosY + (y * time);
}
