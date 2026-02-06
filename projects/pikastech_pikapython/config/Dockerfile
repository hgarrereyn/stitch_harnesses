ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Build static library from src with fuzzing compilers and install into /fuzz/install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure and build core
RUN cmake -S /fuzz/src/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_PROJECT_NAME=pikapython \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build /fuzz/build -j

# Create and build minimal stub implementations for missing optional modules
RUN mkdir -p /fuzz/stubs && cat > /fuzz/stubs/pika_stubs.c <<'EOF'
#include "PikaObj.h"
#include <string.h>
volatile PikaObj* __pikaMain = NULL;
PikaObj* New_builtins(Args* args) { return NULL; }
PikaObj* New_builtins_object(Args* args) { return NULL; }
PikaObj* New_builtins_RangeObj(Args* args) { return NULL; }
PikaObj* New_PikaStdData_List(Args* args) { return NULL; }
void PikaStdData_List___init__(PikaObj* self) {}
PikaObj* New_PikaStdData_Tuple(Args* args) { return NULL; }
void PikaStdData_Tuple___init__(PikaObj* self) {}
PikaObj* New_PikaStdData_Dict(Args* args) { return NULL; }
void PikaStdData_Dict___init__(PikaObj* self) {}
PikaObj* New_PikaStdData_String(Args* args) { return NULL; }
PikaObj* New_PikaStdData_ByteArray(Args* args) { return NULL; }
PikaObj* New_PikaStdLib_SysObj(Args* args) { return NULL; }
PikaObj* New_PikaStdData_FILEIO(Args* args) { return NULL; }
void PikaStdData_FILEIO_init(PikaObj* self, char* name, char* mode) {}
int string_slice(char* s, int a, int b) { return 0; }
int strGetSizeUtf8(char* s) { return (s ? (int)strlen(s) : 0); }
EOF

RUN ${CC} -I/fuzz/src/src -c /fuzz/stubs/pika_stubs.c -o /fuzz/stubs/pika_stubs.o \
 && ar rcs /fuzz/stubs/libpikapython-extras.a /fuzz/stubs/pika_stubs.o

# Install headers and static libraries
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -a /fuzz/src/src/*.h /fuzz/install/include/ \
 && cp -a /fuzz/build/libpikapython-core.a /fuzz/install/lib/ \
 && cp -a /fuzz/stubs/libpikapython-extras.a /fuzz/install/lib/
