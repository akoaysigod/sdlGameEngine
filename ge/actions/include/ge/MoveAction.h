#pragma once

#include "../include/ge/Action.h"

namespace ge {
  class MoveAction: public ge::Action {
  public:
    MoveAction(bool isMoveTo,
               bool isForever,
               int x,
               int y,
               double duration);
    void run(std::shared_ptr<Node> node, double delta);

  private:
    bool isMoveTo;
    int x;
    int sPosX = 0;
    int y;
    int sPosY = 0;

    void moveBy(std::shared_ptr<Node> node, int x, int y);
  };
}
