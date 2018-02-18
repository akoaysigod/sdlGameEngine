#pragma once

#include <SDL.h>

#include <memory>
#include <string>

namespace ge {
class Renderer;

class Texture {
public:
  Texture(std::shared_ptr<SDL_Texture> texture,
          const SDL_Rect &clipRect,
          const int width,
          const int height);
  static Texture init(const std::string &fileName,
                      const std::shared_ptr<Renderer> &renderer);
  Texture make(const SDL_Rect &clipRect);
  SDL_Texture* getCPtr() const;
  SDL_Rect getBounds(int x, int y) const;
  SDL_Rect getClipRect() const;

private:
  std::shared_ptr<SDL_Texture> texture;
  const SDL_Rect clipRect;
  const int width;
  const int height;
};
}
