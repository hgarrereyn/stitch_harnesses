ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools (none strictly required to use headers)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Manually install public headers into /fuzz/install
RUN mkdir -p /fuzz/install/include/afl /fuzz/install/lib/afl /fuzz/install/bin && \
    cp -a include/*.h /fuzz/install/include/afl/
