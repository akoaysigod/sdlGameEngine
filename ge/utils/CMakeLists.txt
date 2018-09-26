add_library(utils
  src/GameTimer.cpp
  src/Point.cpp
  src/Rect.cpp
)

target_include_directories(utils
  PUBLIC include/
  PUBLIC ${SDL_INCLUDE_DIR}
)
