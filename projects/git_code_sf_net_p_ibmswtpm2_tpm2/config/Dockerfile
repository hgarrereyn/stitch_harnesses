ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Build static library from project sources using the provided clang wrappers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Build objects (avoid -Werror) and create a static library, then install headers and lib
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    make -C /fuzz/src/src \
        CC=${CC} \
        CCFLAGS="-Wno-everything -c -O2 -fcommon -DUSE_BIT_FIELD_STRUCTURES=NO -DTPM_POSIX -D_POSIX_ -DTPM_NUVOTON -DSYM_LIB=Ossl -DHASH_LIB=Ossl -DMATH_LIB=TpmBigNum -DBN_MATH_LIB=Ossl -DSIMULATION=1" && \
    ar rcs /fuzz/install/lib/libtpm2sim.a /fuzz/src/src/*.o && \
    ar d /fuzz/install/lib/libtpm2sim.a TPMCmds.o || true && \
    cp /fuzz/src/src/*.h /fuzz/install/include/
