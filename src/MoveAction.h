#pragma once

#include "Action.h"

#include <optional>

namespace ge {
  class MoveAction: public ge::Action {
  public:
    MoveAction(bool isMoveTo,
               bool isForever,
               int x,
               int y,
               double duration,
               std::optional<ActionCompletion> completion);
    void run(Node *node, double delta);

  private:
    bool isMoveTo;
    int x;
    int sPosX = 0;
    int y;
    int sPosY = 0;

    void moveBy(Node *node, int x, int y);
  };
}
