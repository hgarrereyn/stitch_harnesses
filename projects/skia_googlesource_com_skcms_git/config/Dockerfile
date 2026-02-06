ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies required.
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Build a static library manually using the project's source files.
RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include/src; \
    ${CXX} -std=c++11 -O2 -fPIC -c skcms.cc -o skcms.o; \
    ${CXX} -std=c++11 -O2 -fPIC -c src/skcms_TransformBaseline.cc -o skcms_TransformBaseline.o; \
    ${CXX} -std=c++11 -O2 -fPIC -march=x86-64 -mavx2 -mf16c -c src/skcms_TransformHsw.cc -o skcms_TransformHsw.o; \
    ${CXX} -std=c++11 -O2 -fPIC -march=x86-64 -mavx512f -mavx512dq -mavx512cd -mavx512bw -mavx512vl -c src/skcms_TransformSkx.cc -o skcms_TransformSkx.o; \
    ar rcs ${INSTALL_PREFIX}/lib/libskcms.a skcms.o skcms_TransformBaseline.o skcms_TransformHsw.o skcms_TransformSkx.o; \
    cp -v skcms.h ${INSTALL_PREFIX}/include/; \
    cp -v src/skcms_public.h ${INSTALL_PREFIX}/include/src/
