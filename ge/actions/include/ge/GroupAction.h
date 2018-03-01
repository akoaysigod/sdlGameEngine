#pragma once

#include "../include/ge/Action.h"

#include <memory>
#include <vector>

namespace ge {
  class GroupAction: public Action {
  public:
    static GroupAction init(std::vector<std::shared_ptr<Action>> actions,
                            bool isForever);
    void run(Node *node, double delta);

  private:
    GroupAction(std::vector<std::shared_ptr<Action>> actions,
                bool isForever,
                double duration);
    const std::vector<std::shared_ptr<Action>> actions;
  };
}
