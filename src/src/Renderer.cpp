#include "../include/Renderer.h"

#include "../include/Window.h"

using ge::Renderer;

Renderer::Renderer(const ge::Window &window, int red, int green, int blue):
  sdlRenderer(SDL_CreateRenderer(window.getCPtr(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer) {
  SDL_SetRenderDrawColor(sdlRenderer.get(), red, green, blue, 0x0);
}

SDL_Renderer* Renderer::getCPtr() const {
  return sdlRenderer.get();
}

void Renderer::clear() {
  SDL_RenderClear(getCPtr());
}

void Renderer::renderCopy(SDL_Texture *texture, const SDL_Rect &clipRect, const SDL_Rect &rect) const {
  SDL_RenderCopy(getCPtr(), texture, &clipRect, &rect);
}
void Renderer::renderCopyEx(SDL_Texture *texture,
                            const SDL_Rect &clipRect,
                            const SDL_Rect &rect,
                            const double angle) {
  SDL_RenderCopyEx(getCPtr(), texture, &clipRect, &rect, angle, nullptr, SDL_FLIP_NONE);
}

void Renderer::present() {
  SDL_RenderPresent(getCPtr());
}
