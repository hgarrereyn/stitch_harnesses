ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends findutils ca-certificates && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include

WORKDIR /fuzz/src
RUN find groups -type f -name '*.h' -exec install -D "{}" "/fuzz/install/include/{}" \; && \
    find thirdparty -type f -name '*.h' -exec install -D "{}" "/fuzz/install/include/{}" \; || true

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
