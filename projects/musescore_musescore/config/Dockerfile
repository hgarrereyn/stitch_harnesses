ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Install header-only interval tree from MuseScore thirdparty and provide a tiny static lib for linking
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && cp /fuzz/src/thirdparty/intervaltree/IntervalTree.h /fuzz/install/include/ \
    && printf 'int musescore_intervaltree_dummy=0;\n' > /tmp/dummy.cpp \
    && ${CXX} -c /tmp/dummy.cpp -o /tmp/dummy.o \
    && ar rcs /fuzz/install/lib/libintervaltree.a /tmp/dummy.o \
    && rm -f /tmp/dummy.cpp /tmp/dummy.o
