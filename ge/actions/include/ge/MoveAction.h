#pragma once

#include "../include/ge/Action.h"

#include <memory>

namespace ge {
  class MoveAction: public ge::Action {
  public:
    MoveAction(bool isMoveTo,
               bool isForever,
               int x,
               int y,
               double duration);
    void run(std::shared_ptr<Node> node, double delta);

    static std::shared_ptr<MoveAction> makeMoveAction(const int &startX,
                                                      const int &startY,
                                                      const int &toX,
                                                      const int &toY,
                                                      const double &speed);

  private:
    bool isMoveTo;
    int x;
    int sPosX = 0;
    int y;
    int sPosY = 0;

    void moveBy(std::shared_ptr<Node> node, int x, int y);
  };
}
