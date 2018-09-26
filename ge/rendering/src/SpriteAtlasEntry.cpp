#include "../include/ge/SpriteAtlasEntry.h"

using namespace ge;

SpriteAtlasEntry::SpriteAtlasEntry(std::string name, int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}
