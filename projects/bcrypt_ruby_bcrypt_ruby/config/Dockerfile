ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a static C library from the bundled Openwall bcrypt sources (no Ruby needed)
RUN apt-get update && apt-get install -y --no-install-recommends make && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build and install static lib and headers
RUN set -eux; \
    mkdir -p /build/stubinc/ruby; \
    # Provide an empty ruby/util.h so wrapper.c can compile without Ruby
    printf "/* stub for non-Ruby build */\n" > /build/stubinc/ruby/util.h; \
    cd /build; \
    $CC -O2 -I/build/stubinc -c /fuzz/src/ext/mri/crypt_blowfish.c -o crypt_blowfish.o; \
    $CC -O2 -I/build/stubinc -c /fuzz/src/ext/mri/crypt_gensalt.c -o crypt_gensalt.o; \
    $CC -O2 -D__SKIP_GNU -I/build/stubinc -c /fuzz/src/ext/mri/wrapper.c -o wrapper.o; \
    ar rcs libowcrypt.a wrapper.o crypt_blowfish.o crypt_gensalt.o; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    cp libowcrypt.a /fuzz/install/lib/; \
    cp /fuzz/src/ext/mri/ow-crypt.h /fuzz/install/include/; \
    cp /fuzz/src/ext/mri/crypt_blowfish.h /fuzz/install/include/; \
    cp /fuzz/src/ext/mri/crypt_gensalt.h /fuzz/install/include/
