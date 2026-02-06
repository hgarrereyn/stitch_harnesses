ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN bash -lc "set -euxo pipefail && install -d /fuzz/install/include /fuzz/install/lib && cp -a /fuzz/src/cpp/include/cuml /fuzz/install/include/ && echo 'int cuml_dummy(void){return 0;}' > /tmp/cuml_dummy.c && gf_libafl_cc -c /tmp/cuml_dummy.c -o /tmp/cuml_dummy.o && ar rcs /fuzz/install/lib/libcuml.a /tmp/cuml_dummy.o"
