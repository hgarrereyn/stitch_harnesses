ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from the Time utilities (no external GUI deps)
# 1) Create a tiny stub for lvgl's lv_tick_get so Time.cpp can include lvgl/lvgl.h
# 2) Compile Time.cpp and DateStrings.cpp into a static library

RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends ca-certificates build-essential; \
    rm -rf /var/lib/apt/lists/*; \
    mkdir -p /usr/local/include/lvgl; \
    printf '#ifndef LVGL_STUB_H\n#define LVGL_STUB_H\n#include <stdint.h>\n#ifdef __cplusplus\nextern "C" {\n#endif\nuint32_t lv_tick_get(void);\n#ifdef __cplusplus\n}\n#endif\n#endif\n' > /usr/local/include/lvgl/lvgl.h; \
    mkdir -p /fuzz/build; \
    cd /fuzz/build; \
    export CC=gf_libafl_cc CXX=gf_libafl_cxx; \
    ${CXX} -O2 -ffunction-sections -fdata-sections -I/fuzz/src/Software/X-Track/USER/App/Utils/Time -c /fuzz/src/Software/X-Track/USER/App/Utils/Time/Time.cpp -o Time.o; \
    ${CXX} -O2 -ffunction-sections -fdata-sections -I/fuzz/src/Software/X-Track/USER/App/Utils/Time -c /fuzz/src/Software/X-Track/USER/App/Utils/Time/DateStrings.cpp -o DateStrings.o; \
    ar rcs libxtrack_time.a Time.o DateStrings.o; \
    mkdir -p /fuzz/install/lib /fuzz/install/include/XTrack; \
    cp libxtrack_time.a /fuzz/install/lib/; \
    cp /fuzz/src/Software/X-Track/USER/App/Utils/Time/TimeLib.h /fuzz/install/include/XTrack/; \
    cp /fuzz/src/Software/X-Track/USER/App/Utils/Time/Time.h /fuzz/install/include/XTrack/
