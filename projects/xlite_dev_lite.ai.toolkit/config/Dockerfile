ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    cmake \
    make \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Disable CUDA in CMakeLists to avoid requiring a CUDA toolkit
RUN sed -i 's/^set(\s*CMAKE_CUDA_COMPILER.*$/# &/g' /fuzz/src/CMakeLists.txt \
 && sed -i 's/^set(\s*CMAKE_CUDA_ARCHITECTURES.*$/# &/g' /fuzz/src/CMakeLists.txt \
 && sed -i 's/^enable_language(\s*CUDA\s*)/# enable_language(CUDA) disabled for fuzz build/g' /fuzz/src/CMakeLists.txt

# Configure, build, install
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=MinSizeRel \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_TEST=OFF \
    -DENABLE_TENSORRT=OFF \
    -DENABLE_MNN=OFF \
    -DENABLE_NCNN=OFF \
    -DENABLE_TNN=OFF \
 && cmake --build /fuzz/build -j $(nproc) \
 && cmake --install /fuzz/build
