#include "../include/Action.h"

#include <iostream>

using namespace ge;

Action::Action(bool isForever,
               double duration,
               Easing func,
               std::optional<ActionCompletion> completion):
  isForever(isForever),
  duration(duration),
  func(func),
  completion(completion) {}

double Action::pointAtTime() {
  return timer / duration;
  //auto normal = timer / duration;
  //return func.pointAtTime(normal);
}

double Action::getDuration() {
  return duration;
}

void Action::run(Node *node, double delta) {
  timer += delta;

  if (timer >= duration) {
    if (completion.has_value()) {
      (*completion)();
    }

    if (isForever) {
      timer = 0.0;
    }
    else {
      hasCompleted = true;
    }
  }
}

void Action::setCompletion(ActionCompletion completion) {
  this->completion = completion;
}

bool Action::completed() {
  return hasCompleted;
}
