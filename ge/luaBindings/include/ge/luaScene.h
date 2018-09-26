#pragma once

#include <lua.hpp>

#include "../../../nodes/include/ge/Scene.h"

#include "luaRenderer.h"
#include "luaSpriteNode.h"

#include <memory>

using namespace ge;

static const char *kLUASceneName = "GEScene";

static int initScene(lua_State *state) {
  if (lua_gettop(state) != 2) {
    return luaL_error(state, "Expected 2 arguments for GEScene.");
  }

  int width = (int)luaL_checkinteger(state, 1);
  int height = (int)luaL_checkinteger(state, 2);

  size_t sceneSize = sizeof(std::shared_ptr<Scene>);
  void *luaObj = lua_newuserdata(state, sceneSize);
  auto scene = std::make_shared<Scene>(width, height);
  new(luaObj) std::shared_ptr<Scene>(scene);

  luaL_getmetatable(state, kLUASceneName);
  lua_setmetatable(state, -2);

  return 1;
}

static int deinitScene(lua_State *state) {
  auto maybeScene = luaL_checkudata(state, 1, kLUASceneName);
  auto scene = static_cast<std::shared_ptr<Scene> *>(maybeScene);
  scene->reset();
  return 0;
}

static int updateScene(lua_State *state) {
  if (lua_gettop(state) != 2) {
    return luaL_error(state, "Expected 2 arguments for GEScene::update");
  }
  auto maybeScene = luaL_checkudata(state, 1, kLUASceneName);
  auto scene = static_cast<std::shared_ptr<Scene> *>(maybeScene);

  double delta = luaL_checknumber(state, 2);
  (*scene)->update(delta);

  return 0;
}

static int renderScene(lua_State *state) {
  if (lua_gettop(state) != 2) {
    return luaL_error(state, "Expected 2 arguments for GEScene::update");
  }

  auto maybeScene = luaL_checkudata(state, 1, kLUASceneName);
  auto scene = static_cast<std::shared_ptr<Scene> *>(maybeScene);
  auto maybeRenderer = luaL_checkudata(state, 2, kLUARendererName);
  auto renderer = static_cast<std::shared_ptr<Renderer> *>(maybeRenderer);
  (*scene)->render(*renderer);

  return 0;
}

static int addScene(lua_State *state) {
  if (lua_gettop(state) != 2) {
    return luaL_error(state, "Expected 2 arguments for GEScene::update");
  }

  auto maybeScene = luaL_checkudata(state, 1, kLUASceneName);
  auto scene = static_cast<std::shared_ptr<Scene> *>(maybeScene);
  auto maybeSpriteNode = luaL_checkudata(state, 2, kLUASpriteNodeName);
  auto spriteNode = static_cast<std::shared_ptr<SpriteNode> *>(maybeSpriteNode);
  (*scene)->add(*spriteNode);

  return 0;
}

static std::shared_ptr<luaL_Reg> makeSceneFuncs() {
  std::shared_ptr<luaL_Reg> ret(new luaL_Reg[5], std::default_delete<luaL_Reg[]>());
  ret.get()[0] = {"__gc", deinitScene};
  ret.get()[1] = {"update", updateScene};
  ret.get()[2] = {"render", renderScene};
  ret.get()[3] = {"add", addScene};
  ret.get()[4] = {NULL, NULL};
  return ret;
}
