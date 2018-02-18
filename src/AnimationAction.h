#pragma once

#include "Action.h"

#include <vector>

namespace ge {
  class Texture;

  class AnimationAction: public Action {
  public:
    AnimationAction(std::vector<std::shared_ptr<Texture>> frames,
                    double frameTime,
                    std::optional<std::shared_ptr<Texture>> restoreTexture,
                    bool isForever,
                    std::optional<ActionCompletion> completion);
    void run(Node *node, double delta);

  private:
    int frame = 0;
    double currentTime = 0.0;
    const std::vector<std::shared_ptr<Texture>> frames;
    const double frameTime;
    const std::optional<std::shared_ptr<Texture>> restoreTexture;
  };
}
