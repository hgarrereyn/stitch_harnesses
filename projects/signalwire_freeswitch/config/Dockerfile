ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

# Build and install libesl (Event Socket Library) as a static library
RUN set -eux; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/esl; \
    cd /fuzz/src/libs/esl/src; \
    INCDIR=/fuzz/src/libs/esl/src/include; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c cJSON.c -o cJSON.o; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c cJSON_Utils.c -o cJSON_Utils.o; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c esl.c -o esl.o; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c esl_buffer.c -o esl_buffer.o; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c esl_config.c -o esl_config.o; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c esl_event.c -o esl_event.o; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c esl_json.c -o esl_json.o; \
    ${CC} -O2 -fPIC -I"${INCDIR}" -c esl_threadmutex.c -o esl_threadmutex.o; \
    ${CXX} -O2 -fPIC -I"${INCDIR}" -c esl_oop.cpp -o esl_oop.o; \
    ar rcs libesl.a cJSON.o cJSON_Utils.o esl.o esl_buffer.o esl_config.o esl_event.o esl_json.o esl_threadmutex.o esl_oop.o; \
    cp libesl.a ${PREFIX}/lib/; \
    cp ${INCDIR}/*.h ${PREFIX}/include/esl/
