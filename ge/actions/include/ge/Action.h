#pragma once

#include "Easing.h"

#include <functional>
#include <memory>
#include <optional>

namespace ge {
  class Node;

  typedef std::function<void()> ActionCompletion;

  class Action {
  public:
    Action(bool isForever,
           double duration,
           Easing func,
           std::optional<ActionCompletion> completion);
    virtual void run(Node *node, double delta);
    void setCompletion(ActionCompletion completion);
    bool completed();
    void setEasingFunction(Easing func);
    double getDuration();

  protected:
    double timer = 0.0;
    const bool isForever;
    double duration;
    Easing func;
    std::optional<ActionCompletion> completion;
    bool hasCompleted = false;
    double pointAtTime();
  };
}