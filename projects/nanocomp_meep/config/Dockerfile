ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gfortran make \
    libctl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./autogen.sh \
      --prefix=/fuzz/install \
      --without-python \
      --without-scheme \
      --without-hdf5 \
      --with-mpi=no \
      --with-openmp=no

RUN make -j"$(nproc)" && make install
