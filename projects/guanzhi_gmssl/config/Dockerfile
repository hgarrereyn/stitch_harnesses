ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    ocl-icd-opencl-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Install headers
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r include/gmssl /fuzz/install/include/

# Build a minimal static libgmssl.a with SM3 and version APIs to keep build fast
RUN ${CC} -O2 -Iinclude -c src/version.c -o version.o \
 && ${CC} -O2 -Iinclude -c src/sm3.c -o sm3.o \
 && ${CC} -O2 -Iinclude -c src/sm3_hmac.c -o sm3_hmac.o \
 && ${CC} -O2 -Iinclude -c src/sm3_kdf.c -o sm3_kdf.o \
 && ${CC} -O2 -Iinclude -c src/sm3_pbkdf2.c -o sm3_pbkdf2.o \
 && ${CC} -O2 -Iinclude -c src/sm3_digest.c -o sm3_digest.o \
 && ar rcs /fuzz/install/lib/libgmssl.a version.o sm3.o sm3_hmac.o sm3_kdf.o sm3_pbkdf2.o sm3_digest.o \
 && rm -f *.o
