add_library(nodes
  src/CameraNode.cpp
  src/Node.cpp
  src/RectNode.cpp
  src/Scene.cpp
  src/SpriteNode.cpp
)

add_dependencies(nodes actions)

target_include_directories(nodes
  PUBLIC include/
  PUBLIC ${SDL_INCLUDE_DIR}
  PRIVATE ${SDL_IMAGE_INCLUDE_DIR}
)
