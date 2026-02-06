ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal setup: install only the headers we need into /fuzz/install
RUN mkdir -p /fuzz/install/include/deskflow && \
    cp /fuzz/src/src/lib/deskflow/KeyTypes.h /fuzz/install/include/deskflow/ && \
    cp /fuzz/src/src/lib/deskflow/MouseTypes.h /fuzz/install/include/deskflow/ && \
    cp /fuzz/src/src/lib/deskflow/OptionTypes.h /fuzz/install/include/deskflow/
