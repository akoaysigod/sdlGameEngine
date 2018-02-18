#include "../include/AnimationAction.h"

#include "../include/SpriteNode.h"
#include "../include/Texture.h"

#include <iostream>
#include <cstdlib>

using namespace ge;

AnimationAction::AnimationAction(std::vector<std::shared_ptr<Texture>> frames,
                                 double frameTime,
                                 std::optional<std::shared_ptr<Texture>> restoreTexture,
                                 bool isForever,
                                 std::optional<ActionCompletion> completion):
  Action(isForever, 0.0, Easing::linear(), completion),
  frames(frames), frameTime(frameTime), restoreTexture(restoreTexture) {}

void AnimationAction::run(Node *node, double delta) {
  SpriteNode *spriteNode = dynamic_cast<SpriteNode *>(node);
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
    else if (restoreTexture.has_value()) {
      spriteNode->setTexture(*restoreTexture);
    }
  }
}
