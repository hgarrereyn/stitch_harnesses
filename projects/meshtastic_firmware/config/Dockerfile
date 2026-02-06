ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies are required for building the selected library subset

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Build a minimal static library from the self-contained JSON serialization components
RUN mkdir -p build && \
    $CXX -std=c++17 -O2 -fPIC -Isrc/serialization -c src/serialization/JSON.cpp -o build/JSON.o && \
    $CXX -std=c++17 -O2 -fPIC -Isrc/serialization -c src/serialization/JSONValue.cpp -o build/JSONValue.o && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/serialization && \
    ar rcs ${PREFIX}/lib/libmeshtasticjson.a build/JSON.o build/JSONValue.o && \
    cp -v src/serialization/JSON.h src/serialization/JSONValue.h ${PREFIX}/include/serialization/

