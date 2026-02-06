ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies are needed just to compile against the public C++ header.
# Create the install prefix and copy the public header there.
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/modules/trtyolo/infer/trtyolo.hpp /fuzz/install/include/

# Provide a pkgconfig-style hint directory (not strictly required here)
ENV CPATH=/fuzz/install/include:$CPATH \
    LIBRARY_PATH=/fuzz/install/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/fuzz/install/lib:$LD_LIBRARY_PATH
