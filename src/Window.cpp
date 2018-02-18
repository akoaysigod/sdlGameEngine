#include "Window.h"

using ge::Window;

Window::Window(const std::string &name, int positionX, int positionY, int width, int height):
  sdlWindow(SDL_CreateWindow(name.c_str(), positionX, positionY, width, height, 0), SDL_DestroyWindow) {
}

SDL_Window* Window::getCPtr() const {
  return sdlWindow.get();
}
