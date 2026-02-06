ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: just install headers into /fuzz/install to enable building against them
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/turtlebot3_node/include/turtlebot3_node /fuzz/install/include/
