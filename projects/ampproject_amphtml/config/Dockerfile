ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static C++ library from AMP's htmlparser (no external deps)

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Install headers
RUN install -d /fuzz/install/include/cpp && \
    cp -r validator/cpp/htmlparser /fuzz/install/include/cpp/

# Build a small static library from self-contained sources
RUN set -eux; \
    SRC_DIR=validator/cpp/htmlparser; \
    CXXFLAGS="-O2 -fPIC -std=c++17 -Ivalidator"; \
    $CXX $CXXFLAGS -c $SRC_DIR/strings.cc -o /tmp/strings.o; \
    $CXX $CXXFLAGS -c $SRC_DIR/atomutil.cc -o /tmp/atomutil.o; \
    $CXX $CXXFLAGS -c $SRC_DIR/url.cc -o /tmp/url.o; \
    install -d /fuzz/install/lib; \
    ar rcs /fuzz/install/lib/libampparser.a /tmp/strings.o /tmp/atomutil.o /tmp/url.o; \
    rm -f /tmp/strings.o /tmp/atomutil.o /tmp/url.o

ENV CPATH=/fuzz/install/include \
    LIBRARY_PATH=/fuzz/install/lib
