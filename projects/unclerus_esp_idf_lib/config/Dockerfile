ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib /tmp/esp; \
    printf "#ifndef ESP_TIMER_H\n#define ESP_TIMER_H\n#include <stdint.h>\nstatic inline int64_t esp_timer_get_time(void){ return 0; }\n#endif\n" > /tmp/esp/esp_timer.h; \
    cp /tmp/esp/esp_timer.h /fuzz/install/include/; \
    SRC_DIR=/fuzz/src/components; \
    INCS="-I/tmp/esp -I$SRC_DIR/color -I$SRC_DIR/lib8tion -I$SRC_DIR/noise"; \
    gf_libafl_cc -fPIC -O2 $INCS -c "$SRC_DIR/color/color.c" -o /tmp/color.o; \
    gf_libafl_cc -fPIC -O2 $INCS -c "$SRC_DIR/lib8tion/lib8tion.c" -o /tmp/lib8tion.o; \
    gf_libafl_cc -fPIC -O2 $INCS -c "$SRC_DIR/noise/noise.c" -o /tmp/noise.o; \
    ar rcs /fuzz/install/lib/libespidflib.a /tmp/color.o /tmp/lib8tion.o /tmp/noise.o; \
    cp "$SRC_DIR/color"/*.h /fuzz/install/include/; \
    cp "$SRC_DIR/lib8tion/lib8tion.h" /fuzz/install/include/; \
    cp -r "$SRC_DIR/lib8tion/lib8tion" /fuzz/install/include/; \
    cp "$SRC_DIR/noise/noise.h" /fuzz/install/include/
