ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external dependencies required. Build a minimal static library and install header.
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/include ${INSTALL_PREFIX}/lib /fuzz/build; \
    # Build static library manually (CMake file references a missing source in this snapshot)
    ${CXX} -O2 -fPIC -DGUILITE_ON -I/fuzz/src/src -c /fuzz/src/src/core/core.cpp -o /fuzz/build/core.o; \
    ${CXX} -O2 -fPIC -pthread -DGUILITE_ON -I/fuzz/src/src -c /fuzz/src/src/core/adapter/api_linux.cpp -o /fuzz/build/api_linux.o; \
    ${CXX} -O2 -fPIC -DGUILITE_ON -I/fuzz/src/src -c /fuzz/src/src/widgets/widgets.cpp -o /fuzz/build/widgets.o; \
    ar rcs /fuzz/build/libGuiLite.a /fuzz/build/core.o /fuzz/build/api_linux.o /fuzz/build/widgets.o; \
    cp /fuzz/build/libGuiLite.a ${INSTALL_PREFIX}/lib/; \
    cp /fuzz/src/GuiLite.h ${INSTALL_PREFIX}/include/
