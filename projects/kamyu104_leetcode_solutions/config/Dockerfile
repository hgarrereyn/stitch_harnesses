ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies are required

# Build and install a tiny static library that wraps one solution from the repo
# - Provide a simple C API so external programs can link against it easily
ENV SRC=/fuzz/src \
    PREFIX=/fuzz/install \
    BUILD=/tmp/build

RUN mkdir -p ${BUILD} ${PREFIX}/include ${PREFIX}/lib \
 && printf "#ifndef KAMYU_LEETCODE_H\n#define KAMYU_LEETCODE_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint kamyu_sum(int a, int b);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > ${BUILD}/leetcode.h \
 && printf "#include \"C++/add-two-integers.cpp\"\nextern \"C\" int kamyu_sum(int a, int b) {\n    Solution s;\n    return s.sum(a,b);\n}\n" > ${BUILD}/wrapper.cpp \
 && stitch_libafl_cxx -O2 -fPIC -I${SRC} -c ${BUILD}/wrapper.cpp -o ${BUILD}/wrapper.o \
 && ar rcs ${BUILD}/libleetcode.a ${BUILD}/wrapper.o \
 && cp ${BUILD}/libleetcode.a ${PREFIX}/lib/ \
 && cp ${BUILD}/leetcode.h ${PREFIX}/include/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx