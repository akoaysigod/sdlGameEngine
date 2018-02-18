#include "../include/ge/SfxPlayer.h"

#include "../include/ge/MediaLoader.h"

using namespace ge;

SfxPlayer::SfxPlayer(const std::string &name):
  sfx(MediaLoader::loadSfx(name)) {}

void SfxPlayer::play() {
  Mix_PlayChannel(-1, sfx.get(), 0);
}

void SfxPlayer::setVolume(int volume) {
  Mix_VolumeChunk(sfx.get(), volume);
}
