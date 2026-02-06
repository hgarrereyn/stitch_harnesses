ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends g++ && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

RUN make -j"$(nproc)" VARIANT=default CONFIG_WERROR=false CONFIG_NATIVE=false CONFIG_CXX_ALLOCATOR=false SHARED_FLAGS="-pipe -O2 -fPIC -fvisibility=hidden -fstack-protector-strong -Wall -Wextra" LDFLAGS="-Wl,-O1,--as-needed,-z,relro,-z,now"

RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
    && cp include/h_malloc.h /fuzz/install/include/ \
    && cp out/libhardened_malloc.so /fuzz/install/lib/
