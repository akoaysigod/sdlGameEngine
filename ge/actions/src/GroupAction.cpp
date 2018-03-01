#include "../include/ge/GroupAction.h"

using namespace ge;

GroupAction::GroupAction(std::vector<std::shared_ptr<Action>> actions,
                         bool isForever,
                         double duration):
  Action(isForever, duration, Easing::linear()),
  actions(actions) {}

GroupAction GroupAction::init(std::vector<std::shared_ptr<Action>> actions,
                              bool isForever) {
  double duration = 0.0;
  for (auto action: actions) {
    duration += action->getDuration();
  }
  return GroupAction(actions, isForever, duration);
}

void GroupAction::run(Node *node, double delta) {
  for (auto action: actions) {
    action->run(node, delta);
  }
}
