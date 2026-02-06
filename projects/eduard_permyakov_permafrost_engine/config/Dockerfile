ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include ${PREFIX}/include/GL ${PREFIX}/lib

# Copy headers from the existing source tree mounted at /fuzz/src
RUN cp /fuzz/src/src/pf_math.h ${PREFIX}/include/pf_math.h \
    && cp /fuzz/src/deps/GLEW/include/GL/glew.h ${PREFIX}/include/GL/glew.h || true

# Build static library from pf_math.c
WORKDIR /fuzz/src
RUN ${CC} -std=c99 -O2 -fno-strict-aliasing -fwrapv -DGLEW_NO_GLU -I./deps/GLEW/include -c src/pf_math.c -o /tmp/pf_math.o \
    && ar rcs ${PREFIX}/lib/libpfm_math.a /tmp/pf_math.o \
    && ranlib ${PREFIX}/lib/libpfm_math.a

# Done; the test program will be built later
