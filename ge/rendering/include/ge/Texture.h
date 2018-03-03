#pragma once

#include <SDL.h>

#include <memory>
#include <string>

namespace ge {
  class Font;
  class Renderer;

  class Texture {
  public:
    Texture(std::shared_ptr<SDL_Texture> texture,
            const SDL_Rect &clipRect,
            const int width,
            const int height);
    static std::shared_ptr<Texture> init(const std::string &fileName,
                                         const std::shared_ptr<Renderer> &renderer);

    static std::shared_ptr<Texture> initFont(const std::shared_ptr<Font> font,
                                             const std::string &str,
                                             const Uint8 &r,
                                             const Uint8 &g,
                                             const Uint8 &b,
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
