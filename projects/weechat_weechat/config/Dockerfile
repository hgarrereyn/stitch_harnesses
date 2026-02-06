ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    cmake \
    ninja-build \
    libgnutls28-dev \
    libgcrypt20-dev \
    zlib1g-dev \
    libcurl4-openssl-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install WeeChat (static where possible)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja /fuzz/src \
  -DCMAKE_C_COMPILER=${CC} \
  -DCMAKE_CXX_COMPILER=${CXX} \
  -DCMAKE_INSTALL_PREFIX=/fuzz/install \
  -DBUILD_SHARED_LIBS=OFF \
  -DENABLE_NCURSES=OFF \
  -DENABLE_HEADLESS=ON \
  -DENABLE_NLS=OFF \
  -DENABLE_ZSTD=OFF \
  -DENABLE_CJSON=OFF \
  -DENABLE_ALIAS=OFF \
  -DENABLE_BUFLIST=OFF \
  -DENABLE_CHARSET=OFF \
  -DENABLE_EXEC=OFF \
  -DENABLE_FIFO=OFF \
  -DENABLE_FSET=OFF \
  -DENABLE_IRC=OFF \
  -DENABLE_LOGGER=OFF \
  -DENABLE_RELAY=OFF \
  -DENABLE_SCRIPT=OFF \
  -DENABLE_SCRIPTS=OFF \
  -DENABLE_PERL=OFF \
  -DENABLE_PYTHON=OFF \
  -DENABLE_RUBY=OFF \
  -DENABLE_LUA=OFF \
  -DENABLE_TCL=OFF \
  -DENABLE_GUILE=OFF \
  -DENABLE_JAVASCRIPT=OFF \
  -DENABLE_PHP=OFF \
  -DENABLE_SPELL=OFF \
  -DENABLE_ENCHANT=OFF \
  -DENABLE_TRIGGER=OFF \
  -DENABLE_TYPING=OFF \
  -DENABLE_XFER=OFF \
  -DENABLE_MAN=OFF \
  -DENABLE_DOC=OFF \
  -DENABLE_TESTS=OFF \
  -DENABLE_FUZZ=OFF
RUN cmake --build . --target install -- -v
