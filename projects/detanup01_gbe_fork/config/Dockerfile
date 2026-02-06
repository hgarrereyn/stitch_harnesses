ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Build static library for game_overlay_renderer_lib and install headers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN set -eux; \
    # Minimal shim to avoid pulling huge dependency graph
    mkdir -p /tmp/include_shim/dll; \
    printf "#ifndef GBE_SHIM_COMMON_INCLUDES_H\n#define GBE_SHIM_COMMON_INCLUDES_H\n#include <stdint.h>\n#ifdef __cplusplus\nextern \"C\" { }\n#endif\n#ifndef S_API_EXPORT\n#define S_API_EXPORT\n#endif\n#ifndef S_CALLTYPE\n#define S_CALLTYPE\n#endif\ntypedef uint32_t steam_bool;\ntypedef int32_t int32;\ntypedef int16_t int16;\ntypedef unsigned char uint8;\nenum ENotificationPosition {\n  k_EPositionInvalid = 0,\n  k_EPositionTopLeft = 1,\n  k_EPositionTopRight = 2,\n  k_EPositionBottomLeft = 3,\n  k_EPositionBottomRight = 4\n};\n#endif\n" > /tmp/include_shim/dll/common_includes.h; \
    mkdir -p ${PREFIX}/include ${PREFIX}/lib; \
    ${CXX} -O2 -fPIC \
      -I/tmp/include_shim \
      -c /fuzz/src/game_overlay_renderer_lib/game_overlay_renderer_lib.cpp -o /tmp/game_overlay_renderer_lib.o; \
    ar rcs ${PREFIX}/lib/libgame_overlay_renderer.a /tmp/game_overlay_renderer_lib.o; \
    # Install public header
    cp /fuzz/src/game_overlay_renderer_lib/game_overlay_renderer_lib.h ${PREFIX}/include/; 

    # Install dependent headers to satisfy includes (lightweight set) and override with shim
RUN set -eux; \
    mkdir -p ${PREFIX}/include/dll; \
    cp /tmp/include_shim/dll/common_includes.h ${PREFIX}/include/dll/common_includes.h; \
    true
