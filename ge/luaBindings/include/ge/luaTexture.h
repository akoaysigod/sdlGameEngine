#pragma once

#include <lua.hpp>

#include "../../../rendering/include/ge/Texture.h"

#include "luaRenderer.h"

#include <memory>

using namespace ge;

static const char *kLUATextureName = "GETexture";

static int initTexture(lua_State *state) {
  if (lua_gettop(state) != 2) {
    return luaL_error(state, "Expected 2 arguments for GETexture.");
  }

  auto maybeRenderer = luaL_checkudata(state, 1, kLUARendererName);
  auto renderer = static_cast<std::shared_ptr<Renderer> *>(maybeRenderer);
  const char *file = luaL_checkstring(state, 2);

  size_t textureSize = sizeof(std::shared_ptr<Texture>);
  void *luaObj = lua_newuserdata(state, textureSize);
  auto texture = Texture::init(*renderer, file);
  new(luaObj) std::shared_ptr<Texture>(texture);

  luaL_getmetatable(state, kLUATextureName);
  lua_setmetatable(state, -2);

  return 1;
}

static int deinitTexture(lua_State *state) {
  auto maybeTexture = luaL_checkudata(state, 1, kLUATextureName);
  auto texture = static_cast<std::shared_ptr<Texture> *>(maybeTexture);
  texture->reset();
  return 0;
}

static std::shared_ptr<luaL_Reg> makeTextureFuncs() {
  std::shared_ptr<luaL_Reg> ret(new luaL_Reg[2], std::default_delete<luaL_Reg[]>());
  ret.get()[0] = {"__gc", deinitTexture};
  ret.get()[1] = {NULL, NULL};
  return ret;
}
