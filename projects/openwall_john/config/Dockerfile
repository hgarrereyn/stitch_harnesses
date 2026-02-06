ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and prepare minimal headers installation
WORKDIR /fuzz/src/src

# Use the fuzzing compilers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure the project to generate autoconfig headers; no need to build
RUN ./configure --prefix=/fuzz/install --disable-openmp --without-opencl || true

# Install minimal headers needed for simple API usage
RUN mkdir -p /fuzz/install/include && \
    cp -v jumbo.h misc.h autoconfig.h arch.h /fuzz/install/include/
