#include <SDL_keycode.h>

enum KeyPressState {
  EMPTY = 0,
  DOWN,
  UP,
};

struct KeysPressed {
  SDL_Keycode key = SDLK_UNKNOWN;
  SDL_Keymod modifier = KMOD_NONE;
  KeyPressState state = EMPTY;
};
