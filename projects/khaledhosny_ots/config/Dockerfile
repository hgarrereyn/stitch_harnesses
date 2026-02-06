ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      meson ninja-build pkg-config python3 binutils zlib1g-dev && \
    rm -rf /var/lib/apt/lists/*

# Set compilers to the provided fuzzing wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Build the project with Meson (static library)
WORKDIR /fuzz/src
RUN meson setup build \
      --buildtype=release \
      -Ddefault_library=static \
      -Db_ndebug=true && \
    meson compile -C build

# Install headers and create a monolithic static library with all deps via ld -r
RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cp -v include/*.h /fuzz/install/include/; \
    # collect dependency static libraries built by Meson subprojects
    find build/subprojects -type f -name 'lib*.a' -exec cp -v {} /fuzz/install/lib/ \;; \
    # create a single relocatable object that pulls in ALL objects
    ld -r -o /fuzz/install/lib/ots_all.o \
      --whole-archive \
      /fuzz/src/build/libots.a \
      /fuzz/install/lib/lib*.a \
      /usr/lib/x86_64-linux-gnu/libz.a \
      --no-whole-archive || true; \
    ar crs /fuzz/install/lib/libots_full.a /fuzz/install/lib/ots_all.o
