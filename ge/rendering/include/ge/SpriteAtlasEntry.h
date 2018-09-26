#pragma once

#include <string>

namespace ge {
class SpriteAtlasEntry {
public:
  SpriteAtlasEntry(std::string name, int x, int y, int width, int height);
private:
  int x;
  int y;
  int width;
  int height;
};
}
