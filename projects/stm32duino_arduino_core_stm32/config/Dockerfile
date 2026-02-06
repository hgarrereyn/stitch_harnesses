ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools
RUN apt-get update && apt-get install -y --no-install-recommends rsync && rm -rf /var/lib/apt/lists/*

# Install headers and create a tiny static library placeholder
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    rsync -a --exclude 'CMakeLists.txt' /fuzz/src/cores/arduino/ /fuzz/install/include/ && \
    echo "int __stm32duino_placeholder;" > /tmp/dummy.c && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libstm32duino_core.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o

ENV CPATH=/fuzz/install/include
ENV LIBRARY_PATH=/fuzz/install/lib
