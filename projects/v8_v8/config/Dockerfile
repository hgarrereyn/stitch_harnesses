ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$INSTALL_PREFIX/include" "$INSTALL_PREFIX/lib"; \
    cp -r /fuzz/src/include/* "$INSTALL_PREFIX/include/"; \
    ar rcs "$INSTALL_PREFIX/lib/libv8.a"
