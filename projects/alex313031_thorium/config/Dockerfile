ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a static library
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

# Build a static library from pak_src (exclude CLI main.c) and install headers
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/build; \
    $CC -O2 -fPIC -I/fuzz/src/pak_src -c /fuzz/src/pak_src/pak_header.c -o pak_header.o; \
    $CC -O2 -fPIC -I/fuzz/src/pak_src -c /fuzz/src/pak_src/pak_file.c -o pak_file.o; \
    $CC -O2 -fPIC -I/fuzz/src/pak_src -c /fuzz/src/pak_src/pak_file_io.c -o pak_file_io.o; \
    $CC -O2 -fPIC -I/fuzz/src/pak_src -c /fuzz/src/pak_src/pak_get_file_type.c -o pak_get_file_type.o; \
    $CC -O2 -fPIC -I/fuzz/src/pak_src -c /fuzz/src/pak_src/pak_pack.c -o pak_pack.o; \
    ar rcs /fuzz/install/lib/libpak.a pak_header.o pak_file.o pak_file_io.o pak_get_file_type.o pak_pack.o; \
    cp -v /fuzz/src/pak_src/pak_*.h /fuzz/install/include/
