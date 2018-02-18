#pragma once

#include <SDL.h>
#include <string>

namespace ge {
class SpriteAtlasEntry {
public:
  SpriteAtlasEntry(std::string name, int x, int y, int width, int height);
  SDL_Rect getRect();
private:
  int x;
  int y;
  int width;
  int height;
  SDL_Rect rect;
};
}
