ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required tools
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates build-essential && rm -rf /var/lib/apt/lists/*

# Create shim headers for non-arduino environment
RUN mkdir -p /fuzz/shim && \
    printf "#pragma once\nclass Stream {\npublic:\n  virtual ~Stream() {}\n  virtual int readBytes(unsigned char* buf, unsigned int len){return 0;}\n  virtual int write(const unsigned char* buf, unsigned int len){return len;}\n  virtual int write(unsigned char b){return 1;}\n  template<typename T> void print(const T&){}\n  template<typename T> void println(const T&){}\n  void println(){}\n};\n" > /fuzz/shim/Stream.h && \
    printf "#pragma once\n#include <stddef.h>\nclass SHA256 {\npublic:\n  void update(const void*, size_t) {}\n  void finalize(unsigned char*, size_t) {}\n  void resetHMAC(const unsigned char*, size_t) {}\n  void finalizeHMAC(const unsigned char*, size_t, unsigned char*, size_t) {}\n};\n" > /fuzz/shim/SHA256.h && \
    printf "#pragma once\n#include <stddef.h>\nclass AES128 {\npublic:\n  void setKey(const unsigned char*, size_t) {}\n  void encryptBlock(unsigned char*, const unsigned char*) {}\n  void decryptBlock(unsigned char*, const unsigned char*) {}\n};\n" > /fuzz/shim/AES.h && \
    printf "#pragma once\n#include <stddef.h>\nclass Ed25519 {\npublic:\n  static bool verify(const unsigned char*, const unsigned char*, const unsigned char*, int){ return false; }\n};\n" > /fuzz/shim/Ed25519.h

# Build static library
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx AR=ar

RUN mkdir -p /fuzz/build && cd /fuzz/build && \
    INCS="-I/fuzz/src/src -I/fuzz/src/lib/ed25519 -I/fuzz/shim" && \
    set -e; \
    for f in /fuzz/src/lib/ed25519/*.c; do \
      $CC -c $f $INCS -O2 -fPIC -o $(basename $f .c).o; \
    done; \
    for f in /fuzz/src/src/*.cpp; do \
      $CXX -c $f $INCS -O2 -fPIC -o $(basename $f .cpp).o; \
    done; \
    $AR rcs libmeshcore.a *.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp libmeshcore.a /fuzz/install/lib/ && \
    cp /fuzz/src/src/*.h /fuzz/install/include/ && \
    cp /fuzz/shim/*.h /fuzz/install/include/
