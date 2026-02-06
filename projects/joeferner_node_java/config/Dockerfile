ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    default-jdk-headless \
    libnode-dev \
    node-nan \
    make pkg-config ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/node-java
WORKDIR /fuzz/build

# Build a static library from the native sources
RUN set -eux; \
  JAVA_INC=/usr/lib/jvm/default-java/include; \
  JAVA_OS_INC=/usr/lib/jvm/default-java/include/linux; \
  NODE_INC1=/usr/include/node; \
  NODE_INC2=/usr/include/nodejs; \
  NODE_INC3=/usr/include/nodejs/node_modules; \
  CXXFLAGS="-I${NODE_INC1} -I${NODE_INC2} -I${NODE_INC3} -I${NODE_INC3}/nan -I${JAVA_INC} -I${JAVA_OS_INC} -fPIC -O2"; \
  for f in /fuzz/src/src-cpp/*.cpp; do \
    "$CXX" $CXXFLAGS -c "$f"; \
  done; \
  ar rcs libnodejava.a *.o; \
  cp libnodejava.a /fuzz/install/lib/; \
  cp /fuzz/src/src-cpp/*.h /fuzz/install/include/node-java/
