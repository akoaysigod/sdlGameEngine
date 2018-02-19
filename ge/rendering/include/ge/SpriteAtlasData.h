#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

namespace ge {
  struct Entry {
    int x;
    int y;
    int width;
    int height;
  };

  class SpriteAtlasData {
  public:
    SpriteAtlasData() {}
    std::vector<std::string> names;
    std::set<std::string> contents;
    std::map<std::string, Entry> entries;
  };
}
