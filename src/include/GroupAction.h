#pragma once

#include "../include/Action.h"

#include <memory>
#include <optional>
#include <vector>

namespace ge {
  class GroupAction: public Action {
  public:
    static GroupAction init(std::vector<std::shared_ptr<Action>> actions,
                            bool isForever,
                            std::optional<ActionCompletion> completion);
    void run(Node *node, double delta);

  private:
    GroupAction(std::vector<std::shared_ptr<Action>> actions,
                bool isForever,
                double duration,
                std::optional<ActionCompletion> completion);
    const std::vector<std::shared_ptr<Action>> actions;
  };
}
