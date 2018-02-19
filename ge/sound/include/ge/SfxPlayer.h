#pragma once

#include <SDL_mixer.h>

#include <memory>
#include <string>

namespace ge {
  class SfxPlayer {
  public:
    SfxPlayer(const std::string &name);
    void play();
    void setVolume(int volume);

  private:
    std::shared_ptr<Mix_Chunk> sfx;
  };
}
