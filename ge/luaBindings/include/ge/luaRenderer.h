#pragma once

#include <lua.hpp>

#include "luaWindow.h"
#include "../../../rendering/include/ge/Renderer.h"

using namespace ge;

static const char *kLUARendererName = "GERenderer";

static int initRenderer(lua_State *state) {
  if (lua_gettop(state) != 4) {
    return luaL_error(state, "Expected 4 arguments for GEREnderer.");
  }

  auto maybeWindow = luaL_checkudata(state, 1, kLUAWindowName);
  // need to verify this exists?
  auto window = static_cast<std::shared_ptr<Window> *>(maybeWindow);
  int red = (int)luaL_checkinteger(state, 2);
  int green = (int)luaL_checkinteger(state, 3);
  int blue = (int)luaL_checkinteger(state, 4);

  size_t rendererSize = sizeof(std::shared_ptr<Renderer>);
  void *luaObj = lua_newuserdata(state, rendererSize);
  auto renderer = std::make_shared<Renderer>(*window, red, green, blue);
  new(luaObj) std::shared_ptr<Renderer>(renderer);

  luaL_getmetatable(state, kLUARendererName);
  lua_setmetatable(state, -2);

  return 1;
}

static int deinitRenderer(lua_State *state) {
  void *maybeRenderer = luaL_checkudata(state, 1, kLUARendererName);

  auto renderer = static_cast<std::shared_ptr<Renderer> *>(maybeRenderer);
  renderer->reset();

  return 0;
}

static int rendererClear(lua_State *state) {
  void *maybeRenderer = luaL_checkudata(state, 1, kLUARendererName);

  auto renderer = static_cast<std::shared_ptr<Renderer> *>(maybeRenderer);
  (*renderer)->clear();

  return 0;
}

static int rendererPresent(lua_State *state) {
  void *maybeRenderer = luaL_checkudata(state, 1, kLUARendererName);

  auto renderer = static_cast<std::shared_ptr<Renderer> *>(maybeRenderer);
  (*renderer)->present();

  return 0;
}

static std::shared_ptr<luaL_Reg> makeRendererFuncs() {
  std::shared_ptr<luaL_Reg> ret(new luaL_Reg[4], std::default_delete<luaL_Reg[]>());
  ret.get()[0] = {"__gc", deinitRenderer};
  ret.get()[1] = {"clear", rendererClear};
  ret.get()[2] = {"present", rendererPresent};
  ret.get()[3] = {NULL, NULL};
  return ret;
}
