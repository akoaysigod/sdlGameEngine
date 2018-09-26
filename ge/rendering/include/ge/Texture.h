#pragma once

//#include <cstdint>
#include <memory>
#include <string>

struct SDL_Rect;
class SDL_Texture;

namespace ge {
  class Font;
  class Rect;
  class Renderer;

  class Texture {
  public:
    Texture(std::shared_ptr<SDL_Texture> texture,
            const int &x,
            const int &y,
            const int &width,
            const int &height);
    static std::shared_ptr<Texture> init(const std::shared_ptr<Renderer> &renderer,
                                         const std::string &fileName);

    static std::shared_ptr<Texture> initFont(const std::shared_ptr<Font> font,
                                             const std::string &str,
                                             // Uint8 in SDL, this is probably fine
                                             const uint8_t &r,
                                             const uint8_t &g,
                                             const uint8_t &b,
                                             const std::shared_ptr<Renderer> &renderer);
    Texture make(const Rect &clipRect);
    SDL_Texture* getCPtr() const;
    SDL_Rect getBounds(int x, int y) const;
    SDL_Rect getClipRect() const;

    const int width;
    const int height;

  private:
    std::shared_ptr<SDL_Texture> texture;

    const int x;
    const int y;
  };
}
