ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies from Ubuntu repos
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates pkg-config \
    build-essential cmake ninja-build \
    libssl-dev zlib1g-dev \
    libboost-system-dev libboost-iostreams-dev libboost-locale-dev \
    libpugixml-dev \
    libfmt-dev \
    liblua5.4-dev \
    default-libmysqlclient-dev \
 && rm -rf /var/lib/apt/lists/*

# Work around std::format availability on libstdc++ by using fmt::format everywhere and enable chrono formatting
RUN find /fuzz/src/src -name "*.cpp" -type f -print0 | xargs -0 sed -i 's/\bstd::format\s*(/fmt::format(/g' \
 && sed -i '/<fmt\/color.h>/a #include <fmt/chrono.h>' /fuzz/src/src/otpch.h

# Configure and build the project (disable HTTP to avoid Boost::json requirement)
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /fuzz/build \
    -DHTTP=OFF \
    -DBUILD_TESTING=OFF \
    -DUSE_LUAJIT=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

RUN cmake --build /fuzz/build --target tfslib --config Release

# Manually install library and headers (project has no install rules)
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp /fuzz/build/src/libtfslib.a /fuzz/install/lib/ \
 && cp /fuzz/src/src/*.h /fuzz/install/include/
