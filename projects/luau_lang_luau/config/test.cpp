#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "luacode.h"

static void* alloc(void* ud, void* ptr, size_t osize, size_t nsize) {
    (void)ud; (void)osize; // unused
    if (nsize == 0) { free(ptr); return NULL; }
    return realloc(ptr, nsize);
}

int main() {
    lua_State* L = lua_newstate(alloc, NULL);
    if (!L) {
        fprintf(stderr, "failed to create state\n");
        return 1;
    }

    luaL_openlibs(L);

    const char* src = "return 2+2";
    size_t bcsize = 0;
    char* bytecode = luau_compile(src, strlen(src), NULL, &bcsize);
    if (!bytecode) {
        fprintf(stderr, "compile failed\n");
        return 1;
    }

    int loadres = luau_load(L, "chunk", bytecode, bcsize, 0);
    free(bytecode);

    if (loadres != 0) {
        fprintf(stderr, "luau_load failed: %d\n", loadres);
        return 1;
    }

    if (lua_pcall(L, 0, 1, 0) != 0) {
        fprintf(stderr, "pcall failed: %s\n", lua_tostring(L, -1));
        return 1;
    }

    int result = (int)lua_tonumber(L, -1);
    if (result != 4) {
        fprintf(stderr, "unexpected result: %d\n", result);
        return 1;
    }

    // Clean stack
    lua_pop(L, 1);

    // Close state
    lua_close(L);
    printf("OK\n");
    return 0;
}
