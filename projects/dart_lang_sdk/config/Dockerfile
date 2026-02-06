ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from the Dart SDK's C API dynamic linking shim
# and install public headers for consumers.

ENV DEBIAN_FRONTEND=noninteractive

# No extra system deps are needed; use the provided compilers.
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include; \
    # Build static library from dart_api_dl.c
    ${CC} -fPIC -O2 -I/fuzz/src/runtime/include \
      -c /fuzz/src/runtime/include/dart_api_dl.c -o /tmp/dart_api_dl.o; \
    ar rcs ${INSTALL_PREFIX}/lib/libdart_api_dl.a /tmp/dart_api_dl.o; \
    ranlib ${INSTALL_PREFIX}/lib/libdart_api_dl.a; \
    # Install public headers
    cp /fuzz/src/runtime/include/dart_api.h ${INSTALL_PREFIX}/include/; \
    cp /fuzz/src/runtime/include/dart_native_api.h ${INSTALL_PREFIX}/include/; \
    cp /fuzz/src/runtime/include/dart_tools_api.h ${INSTALL_PREFIX}/include/; \
    cp /fuzz/src/runtime/include/dart_embedder_api.h ${INSTALL_PREFIX}/include/; \
    cp /fuzz/src/runtime/include/analyze_snapshot_api.h ${INSTALL_PREFIX}/include/; \
    cp /fuzz/src/runtime/include/dart_version.h ${INSTALL_PREFIX}/include/; \
    cp /fuzz/src/runtime/include/dart_api_dl.h ${INSTALL_PREFIX}/include/
