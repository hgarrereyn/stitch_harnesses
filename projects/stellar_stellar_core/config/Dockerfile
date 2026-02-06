ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: copy a small header-only part of stellar-core for testing/linking
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include/stellar-core/util /fuzz/install/lib \
 && cp -v src/util/Algorithm.h /fuzz/install/include/stellar-core/util/

# Note: full project build requires many dependencies and rust; for fuzzing we only
# need headers for harness compilation.