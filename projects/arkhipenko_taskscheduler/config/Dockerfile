ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools needed
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include && \
    cp -v /fuzz/src/src/TaskScheduler*.h /fuzz/install/include/

# Provide a non-Arduino shim header that defines required hooks as static functions
RUN /bin/sh -c 'printf "%s\n" \
    "#ifndef TS_NONARDUINO_SHIM_H" \
    "#define TS_NONARDUINO_SHIM_H" \
    "#include <chrono>" \
    "#include <thread>" \
    "#include <sched.h>" \
    "static unsigned long _task_millis() {" \
    "  return (unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();" \
    "}" \
    "static unsigned long _task_micros() {" \
    "  return (unsigned long)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();" \
    "}" \
    "static void _task_yield() { sched_yield(); }" \
    "#endif" \
    > /fuzz/install/include/ts_nonarduino_shim.h'
