ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library for the PlistCpp components bundled in this repo

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx INSTALL_PREFIX=/fuzz/install SRC=/fuzz/src

RUN set -eux; \
    mkdir -p "$INSTALL_PREFIX/include" "$INSTALL_PREFIX/lib" /tmp/build; \
    cd /tmp/build; \
    "$CXX" -O2 -fPIC -I"$SRC/src" -I"$SRC" -c "$SRC/src/Plist.cpp" "$SRC/src/PlistDate.cpp" "$SRC/src/pugixml.cpp"; \
    ar rcs libplistcpp.a Plist.o PlistDate.o pugixml.o; \
    cp libplistcpp.a "$INSTALL_PREFIX/lib/"; \
    cp "$SRC/src/Plist.hpp" "$SRC/src/PlistDate.hpp" "$INSTALL_PREFIX/include/"; \
    :
