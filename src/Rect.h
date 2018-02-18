#pragma once

#include <SDL.h>

#include <memory>
#include <iostream>

namespace ge {
  class Rect {
  public:
    static bool collision(const SDL_Rect &one, const SDL_Rect &two) {
      auto result = std::shared_ptr<SDL_Rect>(new SDL_Rect());
      return SDL_IntersectRect(&one, &two, result.get());
    }
  };
}
