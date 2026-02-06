ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build static library from the provided sources
ENV SRC_DIR=/fuzz/src/RaspberryPi_JetsonNano/c/lib \
    INSTALL_PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include/waveshare && \
    mkdir -p /tmp/build && \
    find "$SRC_DIR" -name '*.c' > /tmp/cfiles.list && \
    while IFS= read -r f; do \
      out=/tmp/build/$(basename "$f" .c).o; \
      stitch_libafl_cc -O2 -fPIC -w -I"$SRC_DIR/Config" -I"$SRC_DIR/GUI" -I"$SRC_DIR/Fonts" -I"$SRC_DIR/e-Paper" -c "$f" -o "$out"; \
    done < /tmp/cfiles.list && \
    ar rcs ${INSTALL_PREFIX}/lib/libwaveshare_epaper.a /tmp/build/*.o && \
    mkdir -p ${INSTALL_PREFIX}/include/waveshare/Config ${INSTALL_PREFIX}/include/waveshare/GUI ${INSTALL_PREFIX}/include/waveshare/Fonts ${INSTALL_PREFIX}/include/waveshare/e-Paper && \
    cp -a ${SRC_DIR}/Config/*.h ${INSTALL_PREFIX}/include/waveshare/Config/ && \
    cp -a ${SRC_DIR}/GUI/*.h ${INSTALL_PREFIX}/include/waveshare/GUI/ && \
    cp -a ${SRC_DIR}/Fonts/*.h ${INSTALL_PREFIX}/include/waveshare/Fonts/ && \
    cp -a ${SRC_DIR}/e-Paper/*.h ${INSTALL_PREFIX}/include/waveshare/e-Paper/

