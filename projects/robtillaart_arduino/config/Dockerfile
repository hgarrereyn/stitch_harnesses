ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install

# Prepare install directories and Arduino stub
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib
# Provide a minimal Arduino.h stub so libraries that expect Arduino can compile on host
RUN bash -lc 'printf "%s\n" \
  "#pragma once" \
  "#include <cstddef>" \
  "#include <cstdint>" \
  "#include <cstdlib>" \
  "#include <string>" \
  "using String = std::string;" \
  "#ifndef F" \
  "#define F(x) x" \
  "#endif" \
  "#ifndef ARDUINO_YIELD_STUB" \
  "#define ARDUINO_YIELD_STUB" \
  "inline void yield() {}" \
  "#endif" \
  > ${PREFIX}/include/Arduino.h'

# Build CRC library as a static archive
WORKDIR /fuzz/src/libraries/CRC/src
RUN bash -lc "$CXX -I${PREFIX}/include -c CRC.cpp -o CRC.o"
RUN bash -lc "$CXX -I${PREFIX}/include -c CRC8.cpp -o CRC8.o"
RUN bash -lc "$CXX -I${PREFIX}/include -c CRC12.cpp -o CRC12.o"
RUN bash -lc "$CXX -I${PREFIX}/include -c CRC16.cpp -o CRC16.o"
RUN bash -lc "$CXX -I${PREFIX}/include -c CRC32.cpp -o CRC32.o"
RUN bash -lc "$CXX -I${PREFIX}/include -c CRC64.cpp -o CRC64.o"
RUN bash -lc "$CXX -I${PREFIX}/include -c CrcFastReverse.cpp -o CrcFastReverse.o"
RUN bash -lc "$CXX -I${PREFIX}/include -c FastCRC32.cpp -o FastCRC32.o"
RUN bash -lc "ar rcs ${PREFIX}/lib/libcrc.a CRC.o CRC8.o CRC12.o CRC16.o CRC32.o CRC64.o CrcFastReverse.o FastCRC32.o && ranlib ${PREFIX}/lib/libcrc.a || true"

# Install headers
RUN cp -a /fuzz/src/libraries/CRC/src/*.h ${PREFIX}/include/

WORKDIR /fuzz