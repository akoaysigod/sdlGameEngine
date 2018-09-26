#pragma once

#include <lua.hpp>

#include "../../../controls/include/ge/Keyboard.h"

#include <memory>

using namespace ge;

static const char *kLUAKeyboardName = "GEKeyboard";

static int initKeyboard(lua_State *state) {
  if (lua_gettop(state) != 0) {
    return luaL_error(state, "Expected 0 arguments for GEKeyboard.");
  }

  size_t gameTimerSize = sizeof(std::shared_ptr<Keyboard>);
  auto luaObj = lua_newuserdata(state, gameTimerSize);
  auto keyboard = std::make_shared<Keyboard>();
  new(luaObj) std::shared_ptr<Keyboard>(keyboard);

  luaL_getmetatable(state, kLUAKeyboardName);
  lua_setmetatable(state, -2);

  return 1;
}

static int deinitKeyboard(lua_State *state) {
  auto maybeKeyboard = luaL_checkudata(state, 1, kLUAKeyboardName);
  auto keyboard = static_cast<std::shared_ptr<Keyboard> *>(maybeKeyboard);
  keyboard->reset();
  return 0;
}

static int polledKeyboard(lua_State *state) {
  auto maybeKeyboard = luaL_checkudata(state, 1, kLUAKeyboardName);
  auto keyboard = static_cast<std::shared_ptr<Keyboard> *>(maybeKeyboard);
  auto keyPress = (*keyboard)->polled();
  lua_pushnumber(state, keyPress.key);
  return 1;
}

static std::shared_ptr<luaL_Reg> makeKeyboardFuncs() {
  std::shared_ptr<luaL_Reg> ret(new luaL_Reg[3], std::default_delete<luaL_Reg[]>());
  ret.get()[0] = {"__gc", deinitKeyboard};
  ret.get()[1] = {"polled", polledKeyboard};
  ret.get()[2] = {NULL, NULL};
  return ret;
}
