add_library(sound
)
target_include_directories(sound
  PUBLIC include/
  PRIVATE ${SDL_MIXER_INCLUDE_DIR}
)
