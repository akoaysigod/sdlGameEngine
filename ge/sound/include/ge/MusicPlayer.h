#pragma once

#include <SDL_mixer.h>

#include <string>

namespace ge {
  class MusicPlayer {
  public:
    MusicPlayer(const std::string &name);
    void play();
    void pause();
    void stop();
    void setVolume(int volume);

  private:
    //this can priobab
    std::shared_ptr<Mix_Music> track;
  };
}
