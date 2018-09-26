add_library(luaBindings
  src/InitLua.cpp
)

target_include_directories(luaBindings
  PUBLIC include/
  PRIVATE ${LUA_INCLUDE_DIR}
  # for keybaord stuff, fix that later
  PRIVATE ${SDL_INCLUDE_DIR}
)
