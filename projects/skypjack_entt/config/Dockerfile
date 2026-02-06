ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# EnTT is header-only; just install headers into /fuzz/install
RUN mkdir -p /fuzz/install/include/entt \
 && cp -r /fuzz/src/src/entt/* /fuzz/install/include/entt/
