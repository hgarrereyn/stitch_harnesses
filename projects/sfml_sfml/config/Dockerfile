ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install newer CMake (>=3.28) required by SFML
RUN apt-get update && apt-get install -y --no-install-recommends python3-pip ca-certificates && rm -rf /var/lib/apt/lists/* \
    && pip3 install --no-cache-dir "cmake>=3.28,<3.29" ninja

# Configure and build only the System module as a static library
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DSFML_BUILD_WINDOW=OFF \
    -DSFML_BUILD_GRAPHICS=OFF \
    -DSFML_BUILD_AUDIO=OFF \
    -DSFML_BUILD_NETWORK=OFF \
    -DSFML_USE_SYSTEM_DEPS=ON

RUN cmake --build . --target install --config Release
