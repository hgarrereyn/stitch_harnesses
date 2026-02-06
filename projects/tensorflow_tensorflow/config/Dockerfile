ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a tiny static library from TensorFlow Lite minimal logging components
# and install headers and library to /fuzz/install.

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build and install a minimal static library
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/tensorflow/lite; \
    cd /fuzz/build; \
    $CXX -fPIC -I/fuzz/src -c \
      /fuzz/src/tensorflow/lite/minimal_logging.cc \
      /fuzz/src/tensorflow/lite/minimal_logging_default.cc \
      /fuzz/src/tensorflow/lite/logger.cc; \
    ar rcs /fuzz/install/lib/libtflitemin.a minimal_logging.o minimal_logging_default.o logger.o; \
    cp -a /fuzz/src/tensorflow/lite/minimal_logging.h /fuzz/install/include/tensorflow/lite/; \
    cp -a /fuzz/src/tensorflow/lite/logger.h /fuzz/install/include/tensorflow/lite/
