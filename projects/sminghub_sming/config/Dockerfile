ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install headers and create an empty static library for linkage
RUN install -d /fuzz/install/include/Sming/Core /fuzz/install/lib && \
    cp /fuzz/src/Sming/Core/Delegate.h /fuzz/install/include/Sming/Core/ && \
    printf "!<arch>\n" > /fuzz/install/lib/libsmingmini.a
