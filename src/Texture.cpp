#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"

using namespace ge;

Texture::Texture(std::shared_ptr<SDL_Texture> texture,
                 const SDL_Rect &clipRect,
                 const int width,
                 const int height):
  texture(texture), clipRect(clipRect), width(width), height(height) {}

Texture Texture::init(const std::string &fileName, const Renderer &renderer) {
  auto surface = std::shared_ptr<SDL_Surface>(
    IMG_Load(fileName.c_str()),
    SDL_FreeSurface);
  auto width = surface.get()->w;
  auto height = surface.get()->h;
  auto texture = std::shared_ptr<SDL_Texture>(
    SDL_CreateTextureFromSurface(renderer.getCPtr(), surface.get()),
    SDL_DestroyTexture);
  SDL_Rect clipRect = {0, 0, width, height};
  return Texture(texture, clipRect, width, height);
}

Texture Texture::make(const SDL_Rect &clipRect) {
  return Texture(texture, clipRect, clipRect.w, clipRect.h);
}

SDL_Texture* Texture::getCPtr() const {
  return texture.get();
}

SDL_Rect Texture::getBounds(int x, int y) const {
  return {x, y, width, height};
}

SDL_Rect Texture::getClipRect() const {
  return clipRect;
}
