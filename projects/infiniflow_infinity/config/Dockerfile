ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libthrift-dev libssl-dev libevent-dev libboost-dev ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN mkdir -p /fuzz/install/lib /fuzz/install/include/infinity_client && \
    $CXX -O2 -fPIC -Iclient/cpp -Isrc/network/infinity_thrift -include cstdint -include memory -include set -include map -c client/cpp/infinity_client.cpp -o /tmp/infinity_client.o && \
    $CXX -O2 -fPIC -Iclient/cpp -Isrc/network/infinity_thrift -c src/network/infinity_thrift/InfinityService.cpp -o /tmp/InfinityService.o && \
    $CXX -O2 -fPIC -Iclient/cpp -Isrc/network/infinity_thrift -c src/network/infinity_thrift/infinity_types.cpp -o /tmp/infinity_types.o && \
    ar rcs /fuzz/install/lib/libinfinity_client.a /tmp/infinity_client.o /tmp/InfinityService.o /tmp/infinity_types.o && \
    cp client/cpp/infinity_client.h client/cpp/table_info.h /fuzz/install/include/infinity_client/ && \
    cp src/network/infinity_thrift/InfinityService.h src/network/infinity_thrift/infinity_types.h /fuzz/install/include/infinity_client/
