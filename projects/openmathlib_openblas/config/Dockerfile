ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    make perl python3 \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Build static-only, CBLAS-only library to avoid Fortran/LAPACK dependencies
RUN make -j"$(nproc)" NO_SHARED=1 ONLY_CBLAS=1 && \
    make install PREFIX=${PREFIX} NO_SHARED=1 ONLY_CBLAS=1
