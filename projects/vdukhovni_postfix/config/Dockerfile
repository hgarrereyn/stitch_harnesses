ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
    pkg-config \
    libssl-dev \
 && rm -rf /var/lib/apt/lists/*

# Build only the util static library and install headers/libs to /fuzz/install
WORKDIR /fuzz/src/postfix

# Generate makefiles with our compiler wrappers and disable optional deps
RUN env -u LD_LIBRARY_PATH make makefiles CC=gf_libafl_cc shared=no dynamicmaps=no \
    CCARGS="-DNO_DB -DNO_NIS -DNO_NISPLUS -DNO_PCRE" DEBUG= OPT=

# Build and stage util library and headers
RUN env -u LD_LIBRARY_PATH make -C src/util update

# Install into /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -v lib/libutil.a /fuzz/install/lib/ \
 && cp -v include/*.h /fuzz/install/include/