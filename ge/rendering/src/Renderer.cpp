#include "../include/ge/Renderer.h"

#include "../include/ge/Window.h"

#include <SDL.h>

using ge::Renderer;

Renderer::Renderer(std::shared_ptr<ge::Window> window, int red, int green, int blue):
  r(red), g(green), b(blue),
  sdlRenderer(SDL_CreateRenderer(window->getCPtr(), -1,
                                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
              SDL_DestroyRenderer) {}

SDL_Renderer* Renderer::getCPtr() const {
  return sdlRenderer.get();
}

void Renderer::clear() {
  SDL_RenderClear(getCPtr());
}

void Renderer::renderCopy(SDL_Texture *texture,
                          const SDL_Rect &clipRect,
                          const SDL_Rect &rect) const {
  SDL_RenderCopy(getCPtr(), texture, &clipRect, &rect);
}
void Renderer::renderCopyEx(SDL_Texture *texture,
                            const SDL_Rect &clipRect,
                            const SDL_Rect &rect,
                            const double angle) const {
  SDL_RenderCopyEx(getCPtr(), texture, &clipRect, &rect, angle, nullptr, SDL_FLIP_NONE);
}
void Renderer::renderRect(const SDL_Rect &rect,
                          const int &r,
                          const int &g,
                          const int &b,
                          const int &a) const {
  SDL_SetRenderDrawColor(getCPtr(), r, g, b, a);
  SDL_RenderFillRect(getCPtr(), &rect);
  //technically don't need to set this back if we weren't using an alpha background.
  SDL_SetRenderDrawColor(getCPtr(), this->r, this->g, this->b, 255);
}
void Renderer::present() {
  SDL_RenderPresent(getCPtr());
}
