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

void GroupAction::run(std::shared_ptr<Node> node, double delta) {
  for (auto action: actions) {
    if (!action->completed()) {
      action->run(node, delta);
    }
  }
}
