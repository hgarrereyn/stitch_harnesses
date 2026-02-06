ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    libcurl4-openssl-dev \
 && rm -rf /var/lib/apt/lists/*

# Build static library and install headers
WORKDIR /fuzz/src/server

RUN mkdir -p obj /fuzz/install/lib /fuzz/install/include \
 && stitch_libafl_cc -Iinclude -O2 -c src/argparse.c -o obj/argparse.o \
 && stitch_libafl_cc -Iinclude -O2 -c src/json.c -o obj/json.o \
 && stitch_libafl_cc -Iinclude -O2 -c src/system.c -o obj/system.o \
 && stitch_libafl_cxx -Iinclude -O2 -c src/netban.cpp -o obj/netban.o \
 && stitch_libafl_cxx -Iinclude -O2 -c src/network.cpp -o obj/network.o \
 && stitch_libafl_cxx -Iinclude -O2 -c src/network_client.cpp -o obj/network_client.o \
 && stitch_libafl_cxx -Iinclude -O2 -c src/server.cpp -o obj/server.o \
 && ar rcs /fuzz/install/lib/libserverstatus.a obj/*.o \
 && cp -a include/*.h /fuzz/install/include/ \
 && cp -a src/*.h /fuzz/install/include/
