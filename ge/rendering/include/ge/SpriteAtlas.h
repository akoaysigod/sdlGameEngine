#pragma once

#include "Texture.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ge {
class Renderer;
class SpriteAtlasEntry;

class SpriteAtlas {
public:
  SpriteAtlas(const std::string &atlasFileName,
              Texture texture);

  std::shared_ptr<Texture> operator[](const std::string &name);
  std::shared_ptr<Texture> getTexture(const std::string &name);
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
