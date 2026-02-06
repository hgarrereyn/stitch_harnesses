ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install needed build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build netcdf-c statically with minimal features (no external deps)
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DNETCDF_ENABLE_HDF5=OFF \
    -DNETCDF_ENABLE_HDF4=OFF \
    -DNETCDF_ENABLE_DAP=OFF \
    -DNETCDF_ENABLE_NCZARR=OFF \
    -DNETCDF_ENABLE_REMOTE_FUNCTIONALITY=OFF \
    -DNETCDF_BUILD_UTILITIES=OFF \
    -DNETCDF_ENABLE_TESTS=OFF \
    -DNETCDF_ENABLE_EXAMPLES=OFF \
    -DNETCDF_ENABLE_PLUGINS=OFF \
    -DNETCDF_ENABLE_S3=OFF

RUN cmake --build build --target install --config Release
