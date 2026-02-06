#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <iostream>

int add(int a, int b) { return a + b; }

int main() {
    lua_State* L = luaL_newstate();
    if (!L) return 1;
    luaL_openlibs(L);

    using namespace luabridge;

    getGlobalNamespace(L)
        .addFunction("add", &add);

    if (luaL_dostring(L, "result = add(2, 3)")) {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    LuaRef res = getGlobal(L, "result");
    int r = res.cast<int>();
    std::cout << "Result: " << r << std::endl;

    lua_close(L);
    return r == 5 ? 0 : 1;
}
