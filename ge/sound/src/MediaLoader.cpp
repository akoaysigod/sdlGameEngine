#include "../include/ge/MediaLoader.h"

using namespace ge;

std::shared_ptr<Mix_Music> MediaLoader::loadMusic(const std::string &name) {
  auto track = std::shared_ptr<Mix_Music>(Mix_LoadMUS(name.c_str()), Mix_FreeMusic);
  return track;
}

std::shared_ptr<Mix_Chunk> MediaLoader::loadSfx(const std::string &name) {
  auto sfx = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(name.c_str()), Mix_FreeChunk);
  return sfx;
}
