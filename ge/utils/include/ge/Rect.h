#pragma once

#include <memory>
#include <iostream>

struct SDL_Rect;

namespace ge {
  class Rect {
  public:
    Rect(const int &x, const int &y, const int &width, const int &height);
    static bool collision(const SDL_Rect &one, const SDL_Rect &two);
    SDL_Rect sdlRect();

    int x;
    int y;
    int width;
    int height;
 };
}
