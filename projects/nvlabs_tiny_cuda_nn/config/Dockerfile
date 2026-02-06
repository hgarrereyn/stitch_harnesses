ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install headers only into /fuzz/install to allow building clients against the public API
RUN mkdir -p /fuzz/install/include \
 && cp -r /fuzz/src/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/dependencies/fmt/include /fuzz/install/include/ || true
