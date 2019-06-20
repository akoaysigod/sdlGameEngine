#pragma once

#include "Action.h"

#include <memory>
#include <vector>

namespace ge {
  class Node;

  class SequenceAction: public ge::Action {
  public:
    SequenceAction(std::vector<std::shared_ptr<Action>> &actions, double duration);
    static std::shared_ptr<SequenceAction> init(std::vector<std::shared_ptr<Action>> &actions);
    void run(std::shared_ptr<Node> node, double delta);

  private:
    const std::vector<std::shared_ptr<Action>> actions;
    //std::vector<std::shared_ptr<Action>>::iterator currentAction;
    int currentAction = 0;
  };
}
