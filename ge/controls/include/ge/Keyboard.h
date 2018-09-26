#pragma once

#include "KeysPressed.h"

#include <memory>

class EventHolder;

// TODO: need to come back to this soon
namespace ge {
  class Keyboard {
  public:
    Keyboard();

    KeysPressed polled();
    KeysPressed state();

  private:
    std::shared_ptr<EventHolder> eventHolder;
  };
}
