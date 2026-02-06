ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install only libuuid as a static library into /fuzz/install
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      meson pkg-config python3 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with fuzzing compilers and static libs, enable only libuuid
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN meson setup build \
      --prefix=/fuzz/install \
      -Ddefault_library=static \
      -Dbuild-libuuid=enabled \
      -Dbuild-libblkid=disabled \
      -Dbuild-libmount=disabled \
      -Dbuild-libsmartcols=disabled \
      -Dbuild-libfdisk=disabled \
      -Dbuild-liblastlog2=disabled \
      -Dbuild-pam-lastlog2=disabled \
      -Dbuild-python=disabled \
      -Dprogram-tests=false \
      -Dnls=disabled \
      -Dreadline=disabled \
      -Dncurses=disabled \
      -Dncursesw=disabled \
      -Dslang=disabled \
      -Dsystemd=disabled \
      -Dlibuser=disabled \
      -Dlibpcre2-posix=disabled \
      -Dlibutempter=disabled \
      -Dlibutil=disabled \
      -Daudit=disabled \
      -Dsmack=disabled \
      -Dselinux=disabled \
      -Dzlib=disabled \
      -Dmagic=disabled \
      -Deconf=disabled \
      -Dbtrfs=disabled \
      -Dbuild-bash-completion=disabled

RUN meson compile -C build -v && \
    meson install -C build
