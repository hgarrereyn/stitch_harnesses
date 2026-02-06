ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies (we compile only Lua vendored in the repo)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build a static Lua 5.1 library with the fuzzing compiler wrappers
RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib /tmp/lua-build; \
    cd /tmp/lua-build; \
    for f in /fuzz/src/vendor/lua/src/*.c; do \
        base=$(basename "$f"); \
        # Exclude the standalone interpreter sources from the library
        if [ "$base" = "lua.c" ] || [ "$base" = "luac.c" ]; then continue; fi; \
        stitch_libafl_cc -O2 -fPIC -I/fuzz/src/vendor/lua/src -c "$f" -o "${base%.c}.o"; \
    done; \
    ar rcs /fuzz/install/lib/liblua5.1.a ./*.o; \
    # Install headers required by public SDK
    cp -a /fuzz/src/vendor/lua/src/*.h /fuzz/install/include/; \
    install -m 0644 /fuzz/src/Shared/publicsdk/include/ILuaModuleManager.h /fuzz/install/include/
