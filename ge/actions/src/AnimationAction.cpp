#include "../include/ge/AnimationAction.h"

#include "../../nodes/include/ge/SpriteNode.h"
#include "../../rendering/include/ge/Texture.h"

#include <iostream>
#include <cstdlib>

using namespace ge;

AnimationAction::AnimationAction(std::vector<std::shared_ptr<Texture>> frames,
                                 double frameTime,
                                 std::shared_ptr<Texture> restoreTexture,
                                 bool isForever):
  Action(isForever, 0.0, Easing::linear()),
  frames(frames), frameTime(frameTime), restoreTexture(restoreTexture) {}

void AnimationAction::run(std::shared_ptr<Node> node, double delta) {
  auto spriteNode = std::dynamic_pointer_cast<SpriteNode>(node);
  if (spriteNode == nullptr) {
    std::cout << "Animations can only be used on SpriteNodes.\n";
    std::abort();
  }

  if (currentTime == 0.0 || currentTime >= frameTime) {
    auto texture = frames[frame];
    frame += 1;
    spriteNode->setTexture(texture);
    currentTime = 0.0;
  }

  currentTime += delta;

  if (frame >= frames.size()) {
    Action::run(node, delta);
    if (isForever) {
      frame = 0;
    }
    else if (restoreTexture) {
      spriteNode->setTexture(restoreTexture);
    }
  }
}
