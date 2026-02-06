ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

RUN mkdir -p ${PREFIX}/include/nvdiffrast ${PREFIX}/lib /tmp/build \
 && cd /tmp/build \
 && ${CXX} -O2 -fPIC -I${SRC}/csrc/common \
      -include string -include stdio.h \
      -D'NVDR_CHECK(COND,ERR)=' \
      -D'NVDR_CHECK_CUDA_ERROR(CUDA_CALL)=' \
      -c ${SRC}/csrc/common/texture.cpp -o texture.o \
 && ar rcs libnvdiffrast.a texture.o \
 && cp libnvdiffrast.a ${PREFIX}/lib/ \
 && cp ${SRC}/csrc/common/texture.h ${PREFIX}/include/nvdiffrast/ \
 && cp ${SRC}/csrc/common/framework.h ${PREFIX}/include/nvdiffrast/ \
 && true
