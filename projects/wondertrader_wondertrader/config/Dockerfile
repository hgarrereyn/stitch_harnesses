ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    ninja-build \
    libboost-dev \
    rapidjson-dev \
 && rm -rf /var/lib/apt/lists/*

# Build only WTSUtils static library
WORKDIR /fuzz/build/WTSUtils
RUN cmake -S /fuzz/src/src/WTSUtils -B . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx
RUN cmake --build . -j

# Install artifacts to /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/WTSUtils /fuzz/install/include/Includes /fuzz/install/include/Share /fuzz/install/include/FasterLibs \
 && find /fuzz/build/WTSUtils -name "libWTSUtils.a" -exec cp {} /fuzz/install/lib/ \; \
 && cp -r /fuzz/src/src/WTSUtils/*.h /fuzz/install/include/WTSUtils/ || true \
 && cp -r /fuzz/src/src/WTSUtils/*.hpp /fuzz/install/include/WTSUtils/ || true \
 && cp -r /fuzz/src/src/Includes/* /fuzz/install/include/Includes/ \
 && cp -r /fuzz/src/src/Share/* /fuzz/install/include/Share/ \
 && cp -r /fuzz/src/src/FasterLibs/* /fuzz/install/include/FasterLibs/
