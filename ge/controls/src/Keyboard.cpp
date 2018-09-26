#include "../include/ge/Keyboard.h"

#include <SDL.h>

using namespace ge;

class EventHolder {
public:
  SDL_Event event;
};

Keyboard::Keyboard(): eventHolder(std::make_shared<EventHolder>()) {}

KeysPressed Keyboard::polled() {
  auto e = eventHolder->event;
  KeysPressed ret = {};
  while(SDL_PollEvent(&e) != 0) {
    auto keyState = e.key.keysym.sym;
    if (e.type == SDL_KEYDOWN) {
      ret.state = DOWN;
    }
    else if (e.type == SDL_KEYUP) {
      ret.state = UP;
    }
    ret.key = keyState;
  }
  return ret;
}

KeysPressed Keyboard::state() {
  SDL_PumpEvents();
  //const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

  return {};
}
