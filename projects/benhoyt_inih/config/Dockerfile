ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies required

# Build and install static libraries manually using the required compilers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cd /fuzz/src && \
    ${CC} -O2 -fPIC -I. -c ini.c -o ini.o && \
    ar rcs libinih.a ini.o && \
    ${CXX} -O2 -fPIC -I. -Icpp -c cpp/INIReader.cpp -o INIReader.o && \
    ar rcs libINIReader.a INIReader.o && \
    install -m644 ini.h /fuzz/install/include/ini.h && \
    install -m644 cpp/INIReader.h /fuzz/install/include/INIReader.h && \
    install -m644 libinih.a /fuzz/install/lib/ && \
    install -m644 libINIReader.a /fuzz/install/lib/
