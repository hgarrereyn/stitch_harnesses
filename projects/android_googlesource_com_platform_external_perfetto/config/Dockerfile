ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools if needed
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Install headers and create a minimal static library for linking
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/include/ /fuzz/install/

# Create a tiny dummy static library to satisfy linkage (-lperfetto_c)
RUN echo 'void __perfetto_dummy(){}' > /tmp/dummy.c \
 && gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs /fuzz/install/lib/libperfetto_c.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o
