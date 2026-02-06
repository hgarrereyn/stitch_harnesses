ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install Lua static library
WORKDIR /fuzz/src

RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && make -j"$(nproc)" \
      CC=gf_libafl_cc \
      AR="ar rc" \
      RANLIB=ranlib \
      MYCFLAGS="-DLUA_USE_LINUX" \
      CFLAGS="-Wall -O2 $(MYCFLAGS)" \
      all \
 && cp -v liblua.a /fuzz/install/lib/ \
 && cp -v lua.h lauxlib.h lualib.h luaconf.h /fuzz/install/include/
