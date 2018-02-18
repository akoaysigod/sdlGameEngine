#pragma once

#include <SDL.h>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Texture.h"

namespace ge {
class Renderer;
class SpriteAtlasEntry;

class SpriteAtlas {
public:
  SpriteAtlas(const std::string &atlasFileName,
              Texture texture);

  std::optional<std::shared_ptr<Texture>> operator[](const std::string name);
  std::vector<std::string> getNames();

private:
  std::vector<std::string> names;
  std::map<std::string, std::shared_ptr<SpriteAtlasEntry> > entries;
  std::map<std::string, std::shared_ptr<Texture>> textures;
  int width;
  int height;
  Texture texture;
};
}
