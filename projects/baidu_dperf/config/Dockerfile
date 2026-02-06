ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and DPDK headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential pkg-config dpdk-dev libnuma-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Create install directories
RUN mkdir -p /fuzz/install/lib /fuzz/install/include

# Compile object files with fuzzing compilers and DPDK cflags
RUN set -eux; \
    SRCS="src/socket.c src/config.c src/client.c src/mbuf_cache.c src/udp.c \
          src/port.c src/mbuf.c src/arp.c src/icmp.c src/tcp.c src/tick.c src/http.c \
          src/net_stats.c src/flow.c src/work_space.c src/cpuload.c src/config_keyword.c \
          src/socket_timer.c src/ip.c src/eth.c src/server.c src/dpdk.c src/ctl.c \
          src/icmp6.c src/neigh.c src/vxlan.c src/csum.c src/bond.c src/lldp.c \
          src/rss.c src/ip_list.c src/http_parse.c src/trace.c src/virtio-user.c"; \
    DPDK_CFLAGS=$(pkg-config --cflags libdpdk); \
    for f in $SRCS; do \
        gf_libafl_cc -c $f -o $(basename $f .c).o -I./src -DHTTP_PARSE -DALLOW_EXPERIMENTAL_API $DPDK_CFLAGS; \
    done; \
    ar rcs libdperf.a *.o; \
    cp libdperf.a /fuzz/install/lib/

# Install headers
RUN cp -a src/*.h /fuzz/install/include/

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
