#include "../include/ge/MoveAction.h"

#include "../../nodes/include/ge/Node.h"
#include "../../utils/include/ge/Point.h"

#include <iostream>

using namespace ge;

MoveAction::MoveAction(bool isMoveTo,
                       bool isForever,
                       int x,
                       int y,
                       double duration):
  Action(isForever, duration, Easing::linear()),
  isMoveTo(isMoveTo),
  x(x),
  y(y) {}

std::shared_ptr<MoveAction> MoveAction::makeMoveAction(const int &startX,
                                                       const int &startY,
                                                       const int &toX,
                                                       const int &toY,
                                                       const double &speed) {
  auto duration = speed * ge::Point(startX, startY).distance(ge::Point(toX, toY));
  return std::make_shared<MoveAction>(true, false, toX, toY, duration);
}

void MoveAction::run(std::shared_ptr<Node> node, double delta) {
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

void MoveAction::moveBy(std::shared_ptr<Node> node, int x, int y) {
  auto time = pointAtTime();

  node->x = sPosX + (x * time);
  node->y = sPosY + (y * time);
}
