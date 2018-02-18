#pragma once

#include <SDL.h>
#include <memory>

namespace ge {
class Window;

class Renderer {
public:
  Renderer(const Window &window, int red, int green, int blue);
  SDL_Renderer* getCPtr() const;
  void clear();
  void renderCopy(SDL_Texture *texture, const SDL_Rect &clipRect, const SDL_Rect &rect) const;
  void renderCopyEx(SDL_Texture *texture,
                    const SDL_Rect &clipRect,
                    const SDL_Rect &rect,
                    const double angle);

  void present();
private:
  std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)> sdlRenderer;
};
}
