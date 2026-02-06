ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install the tiny-regex-c component from the repository as a static library
# using the provided fuzzing compiler wrappers.

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${PREFIX}/include ${PREFIX}/lib; \
    cd /fuzz/src/c/meterpreter/source/tiny-regex-c; \
    # Build static library
    ${CC} -O2 -fPIC -c re.c -o re.o; \
    ar rcs libtinyregex.a re.o; \
    cp -v libtinyregex.a ${PREFIX}/lib/; \
    cp -v re.h ${PREFIX}/include/
