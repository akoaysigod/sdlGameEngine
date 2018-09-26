#pragma once

#include <lua.hpp>

namespace ge {
  class InitLua {
  public:
    InitLua();
    ~InitLua();
    bool runScript(const char *name);
    void registerObjects();

  private:
    void registerObject(const char *name,
                        lua_CFunction constructor,
                        luaL_Reg *funcs);

    lua_State *L;
  };
}
