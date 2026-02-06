ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal deps to build gpsd libraries
RUN apt-get update && apt-get install -y --no-install-recommends \
    scons \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Build the libraries (shared to avoid static archive index issues) and install to /fuzz/install
RUN scons -j"$(nproc)" \
    shared=yes \
    gpsd=no \
    gpsdclients=no \
    python=no \
    qt=no \
    ncurses=no \
    dbus_export=no \
    bluez=no \
    usb=no \
    prefix=/fuzz/install

RUN scons -j"$(nproc)" install prefix=/fuzz/install
