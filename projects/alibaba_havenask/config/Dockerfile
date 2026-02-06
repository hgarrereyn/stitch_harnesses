ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies needed to build or run the project
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install

# Build a minimal static autil library from the source tree
# using the required compilers and install headers and library
RUN mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include && \
    mkdir -p /tmp/build && cd /tmp/build && \
    cp -r /fuzz/src/aios/autil/autil ${INSTALL_PREFIX}/include/autil && \
    gf_libafl_cxx -O2 -fPIC -I/fuzz/src/aios/autil \
      -c /fuzz/src/aios/autil/autil/StringUtil.cpp -o StringUtil.o && \
    gf_libafl_cxx -O2 -fPIC -I/fuzz/src/aios/autil \
      -c /fuzz/src/aios/autil/autil/Lock.cpp -o Lock.o && \
    gf_libafl_cxx -O2 -fPIC -I/fuzz/src/aios/autil \
      -c /fuzz/src/aios/autil/autil/TimeUtility.cpp -o TimeUtility.o && \
    gf_libafl_cxx -O2 -fPIC -I/fuzz/src/aios/autil \
      -c /fuzz/src/aios/autil/autil/ShortString.cpp -o ShortString.o && \
    ar rcs ${INSTALL_PREFIX}/lib/libautil.a StringUtil.o Lock.o TimeUtility.o ShortString.o && \
    rm -rf /tmp/build
