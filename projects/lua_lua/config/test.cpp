#include <stdio.h>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int main() {
    lua_State *L = luaL_newstate();
    if (!L) { fprintf(stderr, "failed to create Lua state\n"); return 1; }
    luaL_openlibs(L);
    if (luaL_dostring(L, "return 2+3")) {
        fprintf(stderr, "lua error: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }
    if (!lua_isnumber(L, -1)) { fprintf(stderr, "unexpected type\n"); lua_close(L); return 1; }
    int v = (int)lua_tointeger(L, -1);
    printf("2+3=%d\n", v);
    lua_close(L);
    return 0;
}
