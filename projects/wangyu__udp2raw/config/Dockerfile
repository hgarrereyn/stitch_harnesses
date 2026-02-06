ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install step: no extra system deps required; build tools are preinstalled in base image

# Build and install
RUN mkdir -p /fuzz/install/include /fuzz/install/include/lib /fuzz/install/include/libev /fuzz/install/bin && \
    cd /fuzz/src && \
    make dynamic cc_local=stitch_libafl_cxx && \
    cp -v udp2raw_dynamic /fuzz/install/bin/ || cp -v udp2raw /fuzz/install/bin/ && \
    # Install public headers
    cp -v common.h connection.h encrypt.h fd_manager.h log.h misc.h my_ev.h my_ev_common.h network.h pcap_wrapper.h /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/lib && \
    cp -v lib/md5.h lib/pbkdf2-sha1.h lib/pbkdf2-sha256.h lib/aes-common.h /fuzz/install/include/lib/ && \
    # Provide embedded libev headers for includes
    cp -vr libev/* /fuzz/install/include/libev/
