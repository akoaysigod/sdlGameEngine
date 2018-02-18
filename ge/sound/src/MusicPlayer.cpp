#include "../include/ge/MusicPlayer.h"

#include "../include/ge/MediaLoader.h"

using namespace ge;

MusicPlayer::MusicPlayer(const std::string &name):
  track(MediaLoader::loadMusic(name)) {}

void MusicPlayer::play() {
  if (!Mix_PlayingMusic()) {
    Mix_PlayMusic(track.get(), -1);
  }
  else if (Mix_PausedMusic()) {
    Mix_ResumeMusic();
  }
}

void MusicPlayer::pause() {
  if (Mix_PlayingMusic()) {
    Mix_PauseMusic();
  }
}

void MusicPlayer::stop() {
  Mix_HaltMusic();
}

void MusicPlayer::setVolume(int volume) {
  Mix_VolumeMusic(volume);
}
