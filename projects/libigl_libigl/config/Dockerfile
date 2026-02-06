ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    libeigen3-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and install libigl (header-only interface). Disable optional modules.
WORKDIR /fuzz

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DLIBIGL_INSTALL=ON \
    -DLIBIGL_BUILD_TESTS=OFF \
    -DLIBIGL_BUILD_TUTORIALS=OFF \
    -DLIBIGL_USE_STATIC_LIBRARY=OFF \
    -DLIBIGL_EMBREE=OFF \
    -DLIBIGL_GLFW=OFF \
    -DLIBIGL_IMGUI=OFF \
    -DLIBIGL_OPENGL=OFF \
    -DLIBIGL_STB=OFF \
    -DLIBIGL_PREDICATES=OFF \
    -DLIBIGL_SPECTRA=OFF \
    -DLIBIGL_XML=OFF \
    -DLIBIGL_COPYLEFT_CORE=OFF \
    -DLIBIGL_COPYLEFT_CGAL=OFF \
    -DLIBIGL_COPYLEFT_COMISO=OFF \
    -DLIBIGL_COPYLEFT_TETGEN=OFF \
    -DLIBIGL_RESTRICTED_MATLAB=OFF \
    -DLIBIGL_RESTRICTED_MOSEK=OFF \
    -DLIBIGL_RESTRICTED_TRIANGLE=OFF

RUN cmake --build /fuzz/build --target install --config Release
