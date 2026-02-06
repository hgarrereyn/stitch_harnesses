ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install step: provide header-only nlohmann JSON to /fuzz/install/include
RUN mkdir -p /fuzz/install/include && \
    cp /fuzz/src/agent/php7/third_party/json/json.hpp /fuzz/install/include/
