#pragma once

#include <SDL.h>

#include "../include/Node.h"
#include "../include/Renderable.h"
#include "../include/Texture.h"

#include <memory>

namespace ge {
  class SpriteNode: public Node, public Renderable {
  public:
    SpriteNode(std::shared_ptr<Texture> texture);

    SDL_Rect getBounds();

    //renderable
    void render(const Renderer &renderer);

    std::shared_ptr<Texture> getTexture();
    void setTexture(std::shared_ptr<Texture> texture);

    // hashable
    bool operator==(const Hashable &rhs) const;
    std::string getUUID() const;

  private:
    std::shared_ptr<Texture> texture;
  };
}
