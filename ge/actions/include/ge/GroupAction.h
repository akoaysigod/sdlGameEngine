#pragma once

#include "../include/ge/Action.h"

#include <memory>
#include <vector>

namespace ge {
  class GroupAction: public Action {
  public:
    static GroupAction init(std::vector<std::shared_ptr<Action>> actions,
                            bool isForever);
    void run(std::shared_ptr<Node> node, double delta);

    template <class T>
    std::shared_ptr<T> getAction() {
      for (auto action: actions) {
        auto t = std::dynamic_pointer_cast<T>(action);
        if (t) {
          return t;
        }
      }
      return nullptr;
    }

  private:
    GroupAction(std::vector<std::shared_ptr<Action>> actions,
                bool isForever,
                double duration);
    const std::vector<std::shared_ptr<Action>> actions;
  };
}
