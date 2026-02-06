ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    make \
    pkg-config \
    libtommath-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
# Build static library with libtommath as MPI provider and install
RUN make -j"$(nproc)" \
      CC=gf_libafl_cc \
      CFLAGS="-O2 -fPIC -DUSE_LTM -DLTM_DESC" \
      EXTRALIBS="-ltommath" \
      library \
 && make \
      CC=gf_libafl_cc \
      CFLAGS="-O2 -fPIC -DUSE_LTM -DLTM_DESC" \
      EXTRALIBS="-ltommath" \
      PREFIX=/fuzz/install \
      install
