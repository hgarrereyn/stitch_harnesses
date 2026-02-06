ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN mkdir -p /fuzz/install/include/SuperCollider \
 && cp -r /fuzz/src/include/common /fuzz/install/include/SuperCollider/common \
 && cp -r /fuzz/src/include/plugin_interface /fuzz/install/include/SuperCollider/plugin_interface \
 && cp -r /fuzz/src/include/server /fuzz/install/include/SuperCollider/server \
 && cp -r /fuzz/src/include/lang /fuzz/install/include/SuperCollider/lang \
 && cp /fuzz/src/SCVersion.txt /fuzz/install/include/SuperCollider/SCVersion.txt
