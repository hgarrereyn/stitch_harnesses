ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal image: expose headers for consumers
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include/vicinae \
  && cp -r /fuzz/src/vicinae/include/* /fuzz/install/include/vicinae/
