ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install the wasm3 static library bundled in puerts ThirdParty
# We avoid UE dependencies and only build the pure C wasm3 subset.

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx AR=ar RANLIB=ranlib

WORKDIR /fuzz/src

# Compile wasm3 sources into a static library and install headers
RUN set -eux; \
    srcdir="unreal/Puerts/Source/WasmCore/ThirdPart/wasm3"; \
    build="/tmp/build-wasm3"; \
    install_prefix="/fuzz/install"; \
    mkdir -p "$build" "$install_prefix/lib" "$install_prefix/include/wasm3"; \
    cd "$build"; \
    for c in \
        m3_api_libc.c \
        m3_api_meta_wasi.c \
        m3_api_tracer.c \
        m3_api_uvwasi.c \
        m3_api_wasi.c \
        m3_bind.c \
        m3_code.c \
        m3_compile.c \
        m3_core.c \
        m3_env.c \
        m3_exec.c \
        m3_function.c \
        m3_info.c \
        m3_module.c \
        m3_parse.c; do \
        "$CC" -O2 -fPIC -I"/fuzz/src/$srcdir" -c "/fuzz/src/$srcdir/$c" -o "$c.o"; \
    done; \
    "$AR" rcs libwasm3.a *.o; \
    "$RANLIB" libwasm3.a; \
    cp libwasm3.a "$install_prefix/lib/"; \
    cp "/fuzz/src/$srcdir"/*.h "$install_prefix/include/wasm3/"; \
    echo "Installed wasm3 to $install_prefix"

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
