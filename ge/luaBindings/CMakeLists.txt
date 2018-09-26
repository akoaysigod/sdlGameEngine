add_library(luaBindings
  src/InitLua.cpp
)

target_include_directories(luaBindings
  PUBLIC include/
)
