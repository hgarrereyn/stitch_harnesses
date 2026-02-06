ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra dependencies required

# Build a minimal static library from the subset of Niagara that doesn't require external submodules
# We only compile src/fileutils.cpp into a static lib, and install its header.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx INSTALL_PREFIX=/fuzz/install

RUN mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include && \
    cd /fuzz/src && \
    "$CXX" -O2 -fPIC -c src/fileutils.cpp -o fileutils.o && \
    ar rcs libniagara.a fileutils.o && ranlib libniagara.a && \
    cp libniagara.a ${INSTALL_PREFIX}/lib/ && \
    cp src/fileutils.h ${INSTALL_PREFIX}/include/
