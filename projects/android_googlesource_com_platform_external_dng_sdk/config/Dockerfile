ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include /tmp/build; \
    # Install headers
    cp -a /fuzz/src/source/*.h ${INSTALL_PREFIX}/include/; \
    # Build a minimal static library with the needed objects
    cd /tmp/build; \
    for f in dng_safe_arithmetic.cpp dng_string.cpp dng_date_time.cpp dng_exceptions.cpp dng_mutex.cpp dng_memory.cpp dng_pthread.cpp dng_globals.cpp dng_bottlenecks.cpp dng_reference.cpp; do \
      ${CXX} -I/fuzz/src/source -DqDNGUseXMP=0 -DqDNGThreadSafe=1 -O2 -c /fuzz/src/source/$f -o $(basename $f .cpp).o; \
    done; \
    ar rcs libdng_sdk.a *.o; \
    cp libdng_sdk.a ${INSTALL_PREFIX}/lib/; \
    :
