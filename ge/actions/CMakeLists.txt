add_library(actions
  src/Action.cpp
  src/AnimationAction.cpp
  src/Easing.cpp
  src/GroupAction.cpp
  src/MoveAction.cpp
  src/SequenceAction.cpp
)
target_include_directories(actions
  PUBLIC include/
  PUBLIC ${SDL_INCLUDE_DIR}
  )
