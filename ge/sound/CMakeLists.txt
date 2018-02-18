add_library(sound
  src/MediaLoader.cpp
  src/MusicPlayer.cpp
  src/SfxPlayer.cpp
)
target_include_directories(sound
  PUBLIC include/
  PRIVATE ${SDL_MIXER_INCLUDE_DIR}
)
