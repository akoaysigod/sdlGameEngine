#include "../include/ge/Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../include/ge/Font.h"
#include "../include/ge/Renderer.h"

using namespace ge;

Texture::Texture(std::shared_ptr<SDL_Texture> texture,
                 const SDL_Rect &clipRect,
                 const int width,
                 const int height):
  texture(texture), clipRect(clipRect), width(width), height(height) {}

std::shared_ptr<Texture> Texture::init(const std::string &fileName,
                                       const std::shared_ptr<Renderer> &renderer) {
  auto surface = std::shared_ptr<SDL_Surface>
    (IMG_Load(fileName.c_str()),
     SDL_FreeSurface);
  auto width = surface->w;
  auto height = surface->h;
  auto texture = std::shared_ptr<SDL_Texture>
    (SDL_CreateTextureFromSurface(renderer->getCPtr(), surface.get()),
     SDL_DestroyTexture);
  SDL_Rect clipRect = {0, 0, width, height};
  return std::make_shared<Texture>(texture, clipRect, width, height);
}

std::shared_ptr<Texture> Texture::initFont(const std::shared_ptr<Font> font,
                                           const std::string &str,
                                           const Uint8 &r,
                                           const Uint8 &g,
                                           const Uint8 &b,
                                           const std::shared_ptr<Renderer> &renderer) {
  SDL_Color color = {r, g, b, 255};
  auto surface = std::shared_ptr<SDL_Surface>
    (TTF_RenderText_Solid(font->getCPtr(), str.c_str(), color),
     SDL_FreeSurface);
  auto width = surface->w;
  auto height = surface->h;
  auto texture = std::shared_ptr<SDL_Texture>
    (SDL_CreateTextureFromSurface(renderer->getCPtr(), surface.get()),
     SDL_DestroyTexture);
  SDL_Rect clipRect = {0, 0, width, height};
  return std::make_shared<Texture>(texture, clipRect, width, height);
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
