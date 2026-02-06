ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libglm-dev && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include/glslviewer/tools && \
    cp -v src/core/tools/*.h /fuzz/install/include/glslviewer/tools/
