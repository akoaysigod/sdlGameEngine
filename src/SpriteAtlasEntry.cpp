#include "SpriteAtlasEntry.h"

using namespace ge;

SpriteAtlasEntry::SpriteAtlasEntry(std::string name, int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  rect = {x, y, width, height};
}

SDL_Rect SpriteAtlasEntry::getRect() {
  return rect;
}
