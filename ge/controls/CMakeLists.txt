add_library(controls
  src/Keyboard.cpp
)

target_include_directories(controls
  PUBLIC include/
  PRIVATE ${SDL_INCLUDE_DIR}
)
