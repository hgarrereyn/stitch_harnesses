ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal tools to create a static archive
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends binutils \
 && rm -rf /var/lib/apt/lists/*

# "Install" headers and create an empty static library to link against
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/libparabolic/include/* /fuzz/install/include/ \
 && ar rcs /fuzz/install/lib/libparabolic.a
