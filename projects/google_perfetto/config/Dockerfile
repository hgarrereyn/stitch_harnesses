ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN set -eux; \
    mkdir -p /tmp/build && cd /tmp/build; \
    INC="-I/fuzz/src -I/fuzz/src/include -I/fuzz/src/include/perfetto/base/build_configs/bazel"; \
    CXXFLAGS="-O2 -fPIC -fno-omit-frame-pointer -fvisibility=hidden"; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/base64.cc -o base64.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/crash_keys.cc -o crash_keys.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/ctrl_c_handler.cc -o ctrl_c_handler.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/event_fd.cc -o event_fd.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/file_utils.cc -o file_utils.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/getopt_compat.cc -o getopt_compat.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/lock_free_task_runner.cc -o lock_free_task_runner.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/logging.cc -o logging.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/paged_memory.cc -o paged_memory.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/periodic_task.cc -o periodic_task.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/pipe.cc -o pipe.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/rt_mutex.cc -o rt_mutex.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/scoped_mmap.cc -o scoped_mmap.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/status.cc -o status.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/string_splitter.cc -o string_splitter.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/string_utils.cc -o string_utils.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/string_view.cc -o string_view.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/string_view_splitter.cc -o string_view_splitter.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/subprocess.cc -o subprocess.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/subprocess_posix.cc -o subprocess_posix.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/temp_file.cc -o temp_file.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/thread_checker.cc -o thread_checker.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/thread_task_runner.cc -o thread_task_runner.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/thread_utils.cc -o thread_utils.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/time.cc -o time.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/unix_task_runner.cc -o unix_task_runner.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/utils.cc -o utils.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/uuid.cc -o uuid.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/virtual_destructors.cc -o virtual_destructors.o; \
    $CXX $CXXFLAGS $INC -pthread -c /fuzz/src/src/base/waitable_event.cc -o waitable_event.o; \
    ar rcs libperfetto_base.a *.o; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    cp libperfetto_base.a /fuzz/install/lib/; \
    cp -r /fuzz/src/include/perfetto /fuzz/install/include/
