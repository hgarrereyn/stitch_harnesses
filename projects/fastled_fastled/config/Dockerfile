ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra build dependencies needed; we will install headers only
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# "Install" FastLED headers into /fuzz/install/include
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/src/* /fuzz/install/include/
