#pragma once

#include <SDL_ttf.h>

#include <memory>
#include <string>

namespace ge {
  class Font {
  public:
    Font(const std::shared_ptr<TTF_Font> font);

    static std::shared_ptr<Font> init(const std::string &fileName, const int &size);

    TTF_Font* getCPtr() const;

  private:
    const std::shared_ptr<TTF_Font> font;
  };
}
