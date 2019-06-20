#include "../include/ge/SequenceAction.h"

using namespace ge;

SequenceAction::SequenceAction(std::vector<std::shared_ptr<Action>> &actions, double duration):
  Action(false, duration, Easing::linear()),
  actions(actions) {}

std::shared_ptr<SequenceAction> SequenceAction::init(std::vector<std::shared_ptr<Action>> &actions) {
  double duration = 0.0;
  for (auto &action: actions) {
    duration += action->getDuration();
  }
  return std::make_shared<SequenceAction>(actions, duration);
}

void SequenceAction::run(std::shared_ptr<Node> node, double delta) {
  if (actions[currentAction]->completed()) {
    currentAction += 1;
  }

  if (currentAction >= actions.size()) {
    Action::run(node, delta);
    return;
  }

  actions[currentAction]->run(node, delta);
  Action::run(node, delta);
}
