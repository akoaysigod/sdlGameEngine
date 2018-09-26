#include "../include/ge/InitLua.h"

#include "../include/ge/luaWindow.h"

#include <iostream>

using namespace ge;

InitLua::InitLua() {
  L = luaL_newstate();
  luaL_openlibs(L);
}

InitLua::~InitLua() {
  lua_close(L);
}

void InitLua::registerObject(const char *name,
                             lua_CFunction constructor,
                             luaL_Reg *funcs) {
  lua_register(L, name, constructor);
  luaL_newmetatable(L, name);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, funcs, 0);
  lua_pop(L, 1);
}

bool InitLua::runScript(const char *name) {
  if (luaL_dofile(L, name)) {
    std::cerr << lua_tostring(L, -1);
    return false;
  }
  return true;
}

void InitLua::registerObjects() {
  registerObject(kLUAWindowName, initWindow, makeWindowFuncs().get());
}
