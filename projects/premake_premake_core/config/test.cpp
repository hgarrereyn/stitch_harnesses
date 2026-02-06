#include <stdio.h>
#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>
extern "C" {
#include "premake.h"
}

int main() {
    lua_State* L = luaL_newstate();
    if (!L) { printf("luaL_newstate failed\n"); return 1; }
    luaL_openlibs(L);

    if (premake_init(L) != 0) { printf("premake_init failed\n"); return 1; }

    // Call path.isabsolute("/tmp") and print the boolean result
    lua_getglobal(L, "path");
    lua_getfield(L, -1, "isabsolute");
    lua_pushstring(L, "/tmp");
    if (premake_pcall(L, 1, 1) != 0) {
        premake_handle_lua_error(L);
        lua_close(L);
        return 1;
    }
    int isabs = lua_toboolean(L, -1);
    lua_pop(L, 2); // pop result and path table

    printf("path.isabsolute('/tmp') => %s\n", isabs ? "true" : "false");

    lua_close(L);
    return 0;
}
