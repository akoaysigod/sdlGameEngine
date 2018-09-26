#pragma once

#include <lua.hpp>

#include "../../../rendering/include/ge/Window.h"

#include <memory>

using namespace ge;

static const char *kLUAWindowName= "GEWindow";

static int initWindow(lua_State *state) {
  if (lua_gettop(state) != 5) {
    return luaL_error(state, "Expected 5 arguments for GEWindow.");
  }

  const char *name = luaL_checkstring(state, 1);
  int positionX = (int)luaL_checkinteger(state, 2);
  int positionY = (int)luaL_checkinteger(state, 3);
  int width = (int)luaL_checkinteger(state, 4);
  int height = (int)luaL_checkinteger(state, 5);

  size_t windowSize = sizeof(std::shared_ptr<Window>);
  void *luaObj = lua_newuserdata(state, windowSize);
  auto window = std::make_shared<Window>(name, positionX, positionY, width, height);
  new(luaObj) std::shared_ptr<Window>(window);

  luaL_getmetatable(state, kLUAWindowName);
  lua_setmetatable(state, -2);

  return 1;
}

static int deinitWindow(lua_State *state) {
  void *maybeWindow = luaL_checkudata(state, 1, kLUAWindowName);

  // check if it exists?
  auto window = static_cast<std::shared_ptr<Window> *>(maybeWindow);
  window->reset();

  return 0;
}

//c++17 feature not available on Apple LLVM 10
//std::shared_ptr<luaL_Reg[]> ret(new luaL_Reg[2]);
//ret[0] = {"__gc", deinitWindow};
//ret[1] = {NULL, NULL};
static std::shared_ptr<luaL_Reg> makeWindowFuncs() {
  std::shared_ptr<luaL_Reg> ret(new luaL_Reg[2], std::default_delete<luaL_Reg[]>());
  ret.get()[0] = {"__gc", deinitWindow};
  ret.get()[1] = {NULL, NULL};
  return ret;
  //ret->0 = {NULL, NULL};
  //  static const luaL_Reg windowFuncs[] = {
  //    {"__gc", deinitWindow},
  //    {NULL, NULL}
  //  };
  //  return *windowFuncs;
}
//static const luaL_Reg windowFuncs = {
//  {"__gc", deinitWindow},
//  {NULL, NULL}
//};
