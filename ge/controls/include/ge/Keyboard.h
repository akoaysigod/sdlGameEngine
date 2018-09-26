#pragma once

#include "KeysPressed.h"

#include <memory>

class EventHolder;

// TODO: need to come back to this soon
namespace ge {
  class Keyboard {
    Keyboard();

    KeysPressed polled();
    KeysPressed state();

  private:
    std::unique_ptr<EventHolder> eventHolder;
  };
}
