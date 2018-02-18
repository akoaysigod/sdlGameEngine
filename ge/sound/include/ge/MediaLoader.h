#pragma once

#include <SDL_mixer.h>

#include <memory>
#include <string>

//this should be private once i figure out how to do that kind of shit
namespace ge {
  class MediaLoader {
  public:
    static std::shared_ptr<Mix_Music> loadMusic(const std::string &name);
    static std::shared_ptr<Mix_Chunk> loadSfx(const std::string &name);
  };
}
