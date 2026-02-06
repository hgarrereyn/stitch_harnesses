ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build deps (none needed beyond what's in base for static libsepol)
# Keep image small; avoid unnecessary packages. We disable CIL and shared libs to avoid flex/bison.

WORKDIR /fuzz/src

# Build and install only libsepol as a static library
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

RUN make -C libsepol clean || true \
 && make -C libsepol \
    DISABLE_SHARED=y \
    DISABLE_CIL=y \
    PREFIX=/fuzz/install \
    CC=${CC} \
    install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
ENV LD_LIBRARY_PATH=/fuzz/install/lib:$LD_LIBRARY_PATH
