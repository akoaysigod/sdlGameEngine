#include "../include/ge/Init.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>

using namespace ge;

bool Init::SDL() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cout << SDL_GetError() << std::endl;
    SDL_Quit();
    return false;
  }

  return true;
}

bool Init::SDLAudio() {
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    std::cout << Mix_GetError() << std::endl;
    return false;
  }
  return true;
}

bool Init::SDLTTF() {
  if (TTF_Init()) {
    //check error, is this right?
    return false;
  }
  return true;
}

void Init::quitSDL() {
  SDL_Quit();
}

void Init::quitSDLAudio() {
  Mix_Quit();
}

void Init::quitTTF() {
  TTF_Quit();
}
