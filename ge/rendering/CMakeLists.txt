add_library(rendering
  src/Font.cpp
  src/Renderer.cpp
  src/SpriteAtlas.cpp
  src/SpriteAtlasEntry.cpp
  src/Texture.cpp
  src/View.cpp
  src/Window.cpp
)

add_dependencies(rendering init)

target_include_directories(rendering
  PUBLIC include/
  PUBLIC ${SDL_INCLUDE_DIR}
  PRIVATE ${SDL_IMAGE_INCLUDE_DIR}
  PRIVATE ${SDL_TTF_INCLUDE_DIR}
)
