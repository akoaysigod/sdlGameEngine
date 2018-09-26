#pragma once

#include <lua.hpp>

#include "../../../utils/include/ge/GameTimer.h"

#include <memory>

using namespace ge;

static const char *kLUAGameTimerName = "GEGameTimer";

static int initGameTimer(lua_State *state) {
  if (lua_gettop(state) != 0) {
    return luaL_error(state, "Expected 0 arguments for GEGameTimer.");
  }

  size_t gameTimerSize = sizeof(std::shared_ptr<GameTimer>);
  auto luaObj = lua_newuserdata(state, gameTimerSize);
  auto gameTimer = std::make_shared<GameTimer>();
  new(luaObj) std::shared_ptr<GameTimer>(gameTimer);

  luaL_getmetatable(state, kLUAGameTimerName);
  lua_setmetatable(state, -2);

  return 1;
}

static int deinitGameTimer(lua_State *state) {
  auto maybeGameTimer = luaL_checkudata(state, 1, kLUAGameTimerName);
  auto gameTimer = static_cast<std::shared_ptr<GameTimer> *>(maybeGameTimer);
  gameTimer->reset();
  return 0;
}

static int startCapGameTimer(lua_State *state) {
  auto maybeGameTimer = luaL_checkudata(state, 1, kLUAGameTimerName);
  auto gameTimer = static_cast<std::shared_ptr<GameTimer> *>(maybeGameTimer);
  (*gameTimer)->startCap();
  return 0;
}

static int capFrameRateGameTimer(lua_State *state) {
  auto maybeGameTimer = luaL_checkudata(state, 1, kLUAGameTimerName);
  auto gameTimer = static_cast<std::shared_ptr<GameTimer> *>(maybeGameTimer);
  (*gameTimer)->capFrameRate();
  return 0;
}

static int updateGameTimer(lua_State *state) {
  auto maybeGameTimer = luaL_checkudata(state, 1, kLUAGameTimerName);
  auto gameTimer = static_cast<std::shared_ptr<GameTimer> *>(maybeGameTimer);
  auto delta = (*gameTimer)->update();
  lua_pushnumber(state, delta);
  return 1;
}

static std::shared_ptr<luaL_Reg> makeGameTimerFuncs() {
  std::shared_ptr<luaL_Reg> ret(new luaL_Reg[5], std::default_delete<luaL_Reg[]>());
  ret.get()[0] = {"__gc", deinitGameTimer};
  ret.get()[1] = {"startCap", startCapGameTimer};
  ret.get()[2] = {"capFrameRate", capFrameRateGameTimer};
  ret.get()[3] = {"update", updateGameTimer};
  ret.get()[4] = {NULL, NULL};
  return ret;
}
