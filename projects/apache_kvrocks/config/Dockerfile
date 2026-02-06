ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No heavy build is needed for header-only usage; just install minimal tools
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# Provide a minimal header surface under /fuzz/install/include
RUN mkdir -p /fuzz/install/include/kvrocks \
 && cp /fuzz/src/src/common/time_util.h /fuzz/install/include/kvrocks/ \
 && cp /fuzz/src/src/common/type_util.h /fuzz/install/include/kvrocks/
