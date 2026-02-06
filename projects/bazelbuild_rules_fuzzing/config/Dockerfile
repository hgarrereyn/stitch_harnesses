ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools if needed (none required beyond what's provided).
# Prepare install prefix and build a tiny static library so linking succeeds.
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /fuzz/build \
 && printf '#ifndef RULES_FUZZING_H\n#define RULES_FUZZING_H\nextern "C" void rules_fuzzing_dummy();\n#endif\n' > /fuzz/install/include/rules_fuzzing.h \
 && printf '#include <stddef.h>\nextern "C" void rules_fuzzing_dummy(){}\n' > /fuzz/build/dummy.cpp \
 && CC=stitch_libafl_cc CXX=stitch_libafl_cxx stitch_libafl_cxx -c /fuzz/build/dummy.cpp -o /fuzz/build/dummy.o \
 && ar rcs /fuzz/install/lib/librules_fuzzing.a /fuzz/build/dummy.o

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
