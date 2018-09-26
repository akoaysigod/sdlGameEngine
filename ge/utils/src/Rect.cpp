#include "../include/ge/Rect.h"

#include <SDL.h>

using namespace ge;

Rect::Rect(const int &x, const int &y, const int &width, const int &height):
  x(x), y(y), width(width), height(height) {}

static bool collision(const SDL_Rect &one, const SDL_Rect &two) {
  auto result = std::shared_ptr<SDL_Rect>(new SDL_Rect());
  return SDL_IntersectRect(&one, &two, result.get());
}

SDL_Rect Rect::sdlRect() {
  return {x, y, width, height};
}
