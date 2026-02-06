ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    install -d /fuzz/install/include/tensorflow_serving/util /fuzz/install/lib; \
    cp -v /fuzz/src/tensorflow_serving/util/any_ptr.h /fuzz/install/include/tensorflow_serving/util/; \
    cp -v /fuzz/src/tensorflow_serving/util/executor.h /fuzz/install/include/tensorflow_serving/util/; \
    printf "#include <iostream>\nextern \"C\" void tfserving_util_dummy(void){}\n" > /tmp/dummy.cc; \
    gf_libafl_cxx -O2 -c /tmp/dummy.cc -o /tmp/dummy.o; \
    ar rcs /fuzz/install/lib/libtfserving_util.a /tmp/dummy.o; \
    ranlib /fuzz/install/lib/libtfserving_util.a
