add_library(rendering
  src/Renderer.cpp
  src/SpriteAtlas.cpp
  src/SpriteAtlasEntry.cpp
  src/Texture.cpp
  src/Window.cpp
)
target_include_directories(rendering
  PUBLIC include/
  PUBLIC ${SDL_INCLUDE_DIR}
  PRIVATE ${SDL_IMAGE_INCLUDE_DIR}
)
