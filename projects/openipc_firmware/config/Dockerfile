ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system deps required. We just install header-only MAVLink helpers from the repo.

# Install headers into /fuzz/install
RUN mkdir -p /fuzz/install/include/mavlink

# Copy MAVLink headers from rcjoystick package into install include dir
# This project repo is already mounted at /fuzz/src
RUN cp -r /fuzz/src/general/package/legacy/rcjoystick/src/*.h /fuzz/install/include/mavlink/ && \
    cp -r /fuzz/src/general/package/legacy/rcjoystick/src/common /fuzz/install/include/mavlink/ && \
    cp -r /fuzz/src/general/package/legacy/rcjoystick/src/minimal /fuzz/install/include/mavlink/ && \
    cp -r /fuzz/src/general/package/legacy/rcjoystick/src/standard /fuzz/install/include/mavlink/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Nothing to build; headers only. Ensure directory exists for libs in case linker searches it.
RUN mkdir -p /fuzz/install/lib
