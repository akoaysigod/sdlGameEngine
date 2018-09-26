#pragma once

#include <lua.hpp>

#include "../../../nodes/include/ge/SpriteNode.h"
#include "luaTexture.h"

#include <memory>

using namespace ge;

static const char *kLUASpriteNodeName = "GESpriteNode";

static int initSpriteNode(lua_State *state) {
  if (lua_gettop(state) != 1) {
    return luaL_error(state, "Expected 1 argument for GESpriteNode.");
  }

  auto maybeTexture = luaL_checkudata(state, 1, kLUATextureName);
  auto texture = static_cast<std::shared_ptr<Texture> *>(maybeTexture);

  size_t spriteSize = sizeof(std::shared_ptr<SpriteNode>);
  void *luaObj = lua_newuserdata(state, spriteSize);
  auto sprite = std::make_shared<SpriteNode>(*texture);
  new(luaObj) std::shared_ptr<SpriteNode>(sprite);

  luaL_getmetatable(state, kLUASpriteNodeName);
  lua_setmetatable(state, -2);

  return 1;
}

static int deinitSpriteNode(lua_State *state) {
  void *maybeSpriteNode = luaL_checkudata(state, 1, kLUASpriteNodeName);
  auto spriteNode = static_cast<std::shared_ptr<SpriteNode> *>(maybeSpriteNode);
  spriteNode->reset();
  return 0;
}

static std::shared_ptr<luaL_Reg> makeSpriteNodeFuncs() {
  std::shared_ptr<luaL_Reg> ret(new luaL_Reg[2], std::default_delete<luaL_Reg[]>());
  ret.get()[0] = {"__gc", deinitSpriteNode};
  ret.get()[1] = {NULL, NULL};
  return ret;
}
