ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library, no build needed. Ensure basic build tools present (optional).
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      ninja-build cmake && \
    rm -rf /var/lib/apt/lists/*

# Nothing to build at image build time; sources will be available at /fuzz/src at runtime.
# Include files will be consumed directly from /fuzz/src/include.
