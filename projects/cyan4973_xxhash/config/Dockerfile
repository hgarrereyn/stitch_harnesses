ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends sed gawk && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Use fuzzer compilers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Build only the static library
RUN make -j"$(nproc)" libxxhash.a CC=${CC}

# Install static library, headers, and pkg-config into /fuzz/install
RUN make install_libxxhash.a install_libxxhash.includes install_libxxhash.pc \
    PREFIX=/fuzz/install LIBXXH_DISPATCH=0
