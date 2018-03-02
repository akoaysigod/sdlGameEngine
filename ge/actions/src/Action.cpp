#include "../include/ge/Action.h"

#include <iostream>

using namespace ge;

Action::Action(bool isForever,
               double duration,
               Easing func):
  isForever(isForever),
  duration(duration),
  func(func) {}

double Action::pointAtTime() {
  return timer / duration;
  //auto normal = timer / duration;
  //return func.pointAtTime(normal);
}

double Action::getDuration() {
  return duration;
}

void Action::run(std::shared_ptr<Node> node, double delta) {
  timer += delta;

  if (timer >= duration) {
    if (completion) {
      completion();
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
