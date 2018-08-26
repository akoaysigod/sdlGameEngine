add_library(init
  src/Init.cpp
)
target_include_directories(init
  PUBLIC include/
  PUBLIC ${SDL_INCLUDE_DIR}
)
