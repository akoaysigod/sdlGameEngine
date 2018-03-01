#pragma once

#include "../include/ge/Action.h"

#include <vector>

namespace ge {
  class Texture;

  class AnimationAction: public Action {
  public:
    AnimationAction(std::vector<std::shared_ptr<Texture>> frames,
                    double frameTime,
                    std::shared_ptr<Texture> restoreTexture,
                    bool isForever);
    void run(Node *node, double delta);

  private:
    int frame = 0;
    double currentTime = 0.0;
    const std::vector<std::shared_ptr<Texture>> frames;
    const double frameTime;
    const std::shared_ptr<Texture> restoreTexture;
  };
}
