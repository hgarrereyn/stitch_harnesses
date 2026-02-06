ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libeigen3-dev \
    libgoogle-glog-dev \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from the common module (excluding ROS-dependent sources)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p /fuzz/build-common && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include && \
    cd /fuzz/build-common && \
    SRC_DIR=/fuzz/src/src/core/common && \
    INCDIR=${SRC_DIR}/include && \
    find ${SRC_DIR}/src -name '*.cpp' \
      ! -name 'collision_checker.cpp' \
      ! -name 'visualizer.cpp' \
      -print0 | xargs -0 -I{} ${CXX} -O2 -fPIC -I${INCDIR} -I/usr/include/eigen3 -c {} && \
    ar rcs libcommon.a *.o && \
    cp libcommon.a ${PREFIX}/lib/ && \
    cp -r ${INCDIR}/* ${PREFIX}/include/
