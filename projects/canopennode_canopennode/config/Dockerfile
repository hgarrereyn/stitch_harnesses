ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library with selected CANopenNode components
# We only compile modules that don't require hardware/OD: CO_fifo and CRC16
ENV SRC_DIR=/fuzz/src \
    INSTALL_PREFIX=/fuzz/install

RUN mkdir -p /fuzz/build "$INSTALL_PREFIX/lib" "$INSTALL_PREFIX/include" \
 && cd /fuzz/build \
 && gf_libafl_cc -O2 -fPIC -I"$SRC_DIR" -I"$SRC_DIR/example" \
      -DCO_CONFIG_FIFO=CO_CONFIG_FIFO_ENABLE \
      -c "$SRC_DIR/301/CO_fifo.c" -o CO_fifo.o \
 && gf_libafl_cc -O2 -fPIC -I"$SRC_DIR" -I"$SRC_DIR/example" \
      -c "$SRC_DIR/301/crc16-ccitt.c" -o crc16-ccitt.o \
 && ar rcs libcanopennode.a CO_fifo.o crc16-ccitt.o \
 && cp libcanopennode.a "$INSTALL_PREFIX/lib/"

# Install headers (preserve structure expected by includes)
RUN set -eux; \
    mkdir -p "$INSTALL_PREFIX/include/301" "$INSTALL_PREFIX/include/303" \
             "$INSTALL_PREFIX/include/304" "$INSTALL_PREFIX/include/305" \
             "$INSTALL_PREFIX/include/309" "$INSTALL_PREFIX/include/storage" \
             "$INSTALL_PREFIX/include/extra"; \
    cp "$SRC_DIR/CANopen.h" "$INSTALL_PREFIX/include/"; \
    cp "$SRC_DIR/example/CO_driver_target.h" "$INSTALL_PREFIX/include/"; \
    cp "$SRC_DIR/301"/*.h "$INSTALL_PREFIX/include/301/"; \
    cp "$SRC_DIR/303"/*.h "$INSTALL_PREFIX/include/303/"; \
    cp "$SRC_DIR/304"/*.h "$INSTALL_PREFIX/include/304/"; \
    cp "$SRC_DIR/305"/*.h "$INSTALL_PREFIX/include/305/"; \
    cp "$SRC_DIR/309"/*.h "$INSTALL_PREFIX/include/309/"; \
    cp "$SRC_DIR/storage"/*.h "$INSTALL_PREFIX/include/storage/"; \
    cp "$SRC_DIR/extra"/*.h "$INSTALL_PREFIX/include/extra/";
