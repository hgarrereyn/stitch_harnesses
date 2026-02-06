ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    install -d /fuzz/install/include/fuse; \
    cp -v /fuzz/src/dokan_fuse/include/fuse.h /fuzz/install/include/fuse/; \
    cp -v /fuzz/src/dokan_fuse/include/fuse_common.h /fuzz/install/include/fuse/; \
    cp -v /fuzz/src/dokan_fuse/include/fuse_opt.h /fuzz/install/include/fuse/;

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
