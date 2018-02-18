#include "SpriteAtlas.h"

#include "SpriteAtlasEntry.h"
#include "Renderer.h"
#include "String.h"

#include <iostream>
#include <fstream>
#include <iterator>

#include <SDL_image.h>

using namespace ge;

SpriteAtlas::SpriteAtlas(const std::string &atlasFileName,
                         Texture texture): texture(texture) {
  std::string line;
  std::ifstream file(atlasFileName);
  std::vector<std::string> lines;

  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  }
  else {
    std::cout << "Unable to open file " << atlasFileName << std::endl;
  }

  auto k = lines.begin();
  auto widthHeight = string::split(*k);
  if (widthHeight.size() != 2) {
    //error
    std::cout << "Incorrect format, should begin with width height" << std::endl;
  }
  width = atoi(widthHeight[0].c_str());
  height = atoi(widthHeight[1].c_str());

  for (auto i = lines.begin() + 1; i != lines.end(); i++) {
    auto tokens = string::split(*i);
    if (tokens.size() < 3) {
      //error
      std::cout << "Incorrect format, should be name x y" << std::endl;
    }

    std::string name = tokens[0];
    names.push_back(name);
    int x = atoi(tokens[1].c_str());
    int y = atoi(tokens[2].c_str());

    auto entry = std::make_shared<SpriteAtlasEntry>(name, x, y, width, height);
    entries[name] = entry;
  }
}

//make a map for std::shared so they don't keep getting made
std::optional<std::shared_ptr<Texture>> SpriteAtlas::operator[](const std::string name) {
  auto entry = entries[name];
  if (!entry) {
    return {};
  }

  auto cachedTexture = textures[name];
  if (cachedTexture != nullptr) {
    return std::optional<std::shared_ptr<Texture>>(cachedTexture);
  }

  SDL_Rect rect = entry->getRect();
  auto newTexture = std::make_shared<Texture>(texture.make(rect));
    textures[name] = newTexture;
  return std::optional<std::shared_ptr<Texture>>(newTexture);
}

std::vector<std::string> SpriteAtlas::getNames() {
  return names;
}
