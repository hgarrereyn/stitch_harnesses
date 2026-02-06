ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf automake libtool pkg-config make gettext \
    libdbus-1-dev libexpat1-dev \
    && rm -rf /var/lib/apt/lists/*

# Build and install avahi with static libraries only and minimal features
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Generate the configure script without running configure
ENV NOCONFIGURE=1
RUN ./autogen.sh

# Configure with minimal dependencies, static libs only, and install prefix
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared --enable-static \
    --disable-glib --disable-gobject \
    --disable-qt3 --disable-qt4 --disable-qt5 \
    --disable-gtk --disable-gtk3 \
    --disable-libevent \
    --disable-python --disable-pygobject --disable-python-dbus \
    --disable-mono --disable-monodoc \
    --disable-libdaemon \
    --disable-libsystemd \
    --disable-gdbm \
    --disable-manpages

RUN make -j"$(nproc)" && make install
