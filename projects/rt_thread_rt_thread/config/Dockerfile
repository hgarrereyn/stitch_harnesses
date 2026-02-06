ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib

# Provide a minimal rtconfig.h suitable for building the kernel on POSIX
RUN cat > /fuzz/build/rtconfig.h <<'EOF'
#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__
/* Basic kernel configuration */
#define RT_NAME_MAX 12
#define RT_CPUS_NR 1
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 100
#define RT_USING_OVERFLOW_CHECK
/* Enable basic hook infra (some code references it) */
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
/* Memory management */
#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_SMALL_MEM_AS_HEAP
#define RT_USING_HEAP
/* IPC primitives */
#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
/* Debug options (harmless for build) */
#define RT_USING_DEBUG
#define RT_DEBUGING_ASSERT
#define RT_DEBUGING_COLOR
#define RT_DEBUGING_CONTEXT
/* Backtrace depth (used by some headers) */
#define RT_BACKTRACE_LEVEL_MAX_NR 32
#endif /* RT_CONFIG_H__ */
EOF

# Build static library from selected kernel sources (UP only) and POSIX sim port
WORKDIR /fuzz/src
RUN bash -lc 'set -euo pipefail; \
  mkdir -p /fuzz/build/obj; \
  CFLAGS="-I/fuzz/src/include -I/fuzz/build -D__RTTHREAD__ -D__RT_KERNEL_SOURCE__ -pthread -include string.h -fno-builtin"; \
  SRC_LIST="src/clock.c src/components.c src/cpu_up.c src/defunct.c src/idle.c src/ipc.c src/irq.c src/kservice.c src/mem.c src/memheap.c src/mempool.c src/object.c src/scheduler_comm.c src/scheduler_up.c src/slab.c src/thread.c src/timer.c libcpu/sim/posix/cpu_port.c libcpu/sim/posix/startup.c src/klibc/kstring.c src/klibc/kstdio.c src/klibc/kerrno.c src/klibc/rt_vsnprintf_tiny.c src/klibc/rt_vsscanf.c"; \
  for f in $SRC_LIST; do \
    echo "Compiling $f"; \
    $CC $CFLAGS -c "$f" -o "/fuzz/build/obj/$(basename "${f}" .c).o"; \
  done; \
  ar rcs /fuzz/install/lib/librtthread.a /fuzz/build/obj/*.o; \
  ranlib /fuzz/install/lib/librtthread.a'

# Install public headers and the generated configuration header
RUN cp -r /fuzz/src/include/* /fuzz/install/include/ && cp /fuzz/build/rtconfig.h /fuzz/install/include/
