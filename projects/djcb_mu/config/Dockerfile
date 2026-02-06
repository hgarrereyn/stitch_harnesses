ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson ninja-build pkg-config \
    libglib2.0-dev \
    libgmime-3.0-dev libxapian-dev ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Configure, build
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN meson setup build \
      --prefix=/fuzz/install \
      -Dtests=disabled \
      -Dguile=disabled \
      -Dscm=disabled \
      -Dreadline=disabled \
      -Dcld2=disabled \
      -Duse-embedded-fmt=true \
      -Duse-embedded-cli11=true && \
    meson compile -C build -j$(nproc)

# "Install" static libs and headers manually
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include/mu/utils /fuzz/install/include/mu/message; \
    cp build/lib/libmu.a /fuzz/install/lib/; \
    cp build/lib/utils/libmu-utils.a /fuzz/install/lib/; \
    cp build/lib/message/libmu-message.a /fuzz/install/lib/; \
    # headers (both flat and in subdirs for convenience)
    cp lib/*.hh /fuzz/install/include/mu/; \
    cp lib/utils/*.hh /fuzz/install/include/mu/; \
    cp lib/utils/*.hh /fuzz/install/include/mu/utils/; \
    cp lib/message/*.hh /fuzz/install/include/mu/; \
    cp lib/message/*.hh /fuzz/install/include/mu/message/; \
    # provide embedded fmt and tl::optional headers for public includes
    mkdir -p /fuzz/install/include; \
    cp -r thirdparty/fmt/fmt /fuzz/install/include/; \
    cp -r thirdparty/tl /fuzz/install/include/; \
    # provide generated config.h expected by some headers/sources
    cp build/config.h /fuzz/install/include/mu/
