#pragma once

#include "SpriteAtlasData.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ge {
  class Renderer;
  class Texture;
  class SpriteAtlasEntry;

  class SpriteAtlas {
  public:
    //SpriteAtlas(const std::string &atlasFileName,
    //            Texture texture);
    SpriteAtlas(const SpriteAtlasData &data,
                std::shared_ptr<Texture> texture);

    std::shared_ptr<Texture> operator[](const std::string &name);
    std::shared_ptr<Texture> getTexture(const std::string &name);
    std::vector<std::string> getNames();

  private:
    SpriteAtlasData data;
    //std::vector<std::string> names;
    //std::map<std::string, std::shared_ptr<SpriteAtlasEntry> > entries;
    std::map<std::string, std::shared_ptr<Texture>> textures;
    //int width;
    //int height;
    std::shared_ptr<Texture> texture;
  };
}
