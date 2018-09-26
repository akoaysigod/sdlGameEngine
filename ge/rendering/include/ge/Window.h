#pragma once

#include <memory>
#include <string>

// will this work?
class SDL_Window;

namespace ge {
class Window {
public:
  Window(const std::string &name, int positionX, int positionY, int width, int height);
  SDL_Window* getCPtr() const;
private:
  std::unique_ptr<SDL_Window, void(*)(SDL_Window *)> sdlWindow;
};
}
