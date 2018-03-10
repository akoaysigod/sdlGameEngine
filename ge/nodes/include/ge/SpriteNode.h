#pragma once

#include <SDL.h>

#include "Node.h"
#include "../../rendering/include/ge/Renderable.h"
#include "../../rendering/include/ge/Texture.h"

#include <memory>

namespace ge {
  class Texture;

  class SpriteNode: public Node, public Renderable {
  public:
    SpriteNode(std::shared_ptr<Texture> texture);

    //renderable
    void render(const std::shared_ptr<Renderer> &renderer);

    std::shared_ptr<Texture> getTexture();
    void setTexture(std::shared_ptr<Texture> texture);

  private:
    std::shared_ptr<Texture> texture;
  };
}
