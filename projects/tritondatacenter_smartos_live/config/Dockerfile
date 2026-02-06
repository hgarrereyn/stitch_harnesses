ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a tiny static library from src/nomknod.c and install headers/libs
# Compilers are provided by the base image (clang-17 wrappers):
#   C:  stitch_libafl_cc
#   C++: stitch_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/src; \
    stitch_libafl_cc -O2 -fno-omit-frame-pointer -g -c src/nomknod.c -o /tmp/nomknod.o; \
    ar rcs /fuzz/install/lib/libnomknod.a /tmp/nomknod.o; \
    rm -f /tmp/nomknod.o; \
    printf '%s\n' \
      '#ifndef SMARTOS_NOMKNOD_H' \
      '#define SMARTOS_NOMKNOD_H' \
      '' \
      '#include <sys/types.h>' \
      '#include <sys/stat.h>' \
      '' \
      '#ifdef __cplusplus' \
      'extern "C" {' \
      '#endif' \
      '' \
      'int mknod(const char *path, mode_t mode, dev_t dev);' \
      'int mknodat(int fd, const char *path, mode_t mode, dev_t dev);' \
      '' \
      '#ifdef __cplusplus' \
      '}' \
      '#endif' \
      '' \
      '#endif /* SMARTOS_NOMKNOD_H */' \
      > /fuzz/install/include/nomknod.h;
