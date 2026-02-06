ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: ICU headers and glog
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        libicu-dev \
        libgoogle-glog-dev \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build static library manually to avoid networked CMake dependencies
WORKDIR /fuzz/src/clients/cpp

# 1) Build the tool that converts the model to a C include
RUN ${CXX} -O2 -std=c++17 -o build_model_inc build_model_inc.cpp -lpthread

# 2) Generate the model include used by the library
RUN ./build_model_inc resources/zawgyiUnicodeModel.dat zawgyi_model_data.inc

# 3) Build the static library
# - Depends on glog and ICU headers (unicode/utf8.h)
RUN ${CXX} -O2 -std=c++17 -I/fuzz/src/clients/cpp -c zawgyi_detector.cpp -o zawgyi_detector.o
RUN ar rcs libmyanmartools.a zawgyi_detector.o

# 4) Install headers and static library
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp public/myanmartools.h /fuzz/install/include/ && \
    cp libmyanmartools.a /fuzz/install/lib/

WORKDIR /
