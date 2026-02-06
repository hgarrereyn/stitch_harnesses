ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /fuzz/build \
 && cp -r /fuzz/src/include/* /fuzz/install/include/

# Build a minimal static library providing the public C API symbols so headers can be linked
RUN cat > /fuzz/build/maa_stub.cpp <<'EOF'
#include <stdint.h>
#include <string.h>
#include "AsstCaller.h"

extern "C" {

static const char* kVer = "0.0.0-stub";

AsstBool ASSTAPI AsstSetUserDir(const char* /*path*/) { return 1; }
AsstBool ASSTAPI AsstLoadResource(const char* /*path*/) { return 1; }
AsstBool ASSTAPI AsstSetStaticOption(AsstStaticOptionKey /*key*/, const char* /*value*/) { return 1; }

AsstHandle ASSTAPI AsstCreate() { return (AsstHandle)0x1; }
AsstHandle ASSTAPI AsstCreateEx(AsstApiCallback /*callback*/, void* /*custom_arg*/) { return (AsstHandle)0x1; }
void ASSTAPI AsstDestroy(AsstHandle /*handle*/) { }

AsstBool ASSTAPI AsstSetInstanceOption(AsstHandle /*handle*/, AsstInstanceOptionKey /*key*/, const char* /*value*/) { return 1; }

AsstBool ASSTAPI AsstConnect(AsstHandle /*handle*/, const char* /*adb_path*/, const char* /*address*/, const char* /*config*/) { return 1; }

AsstTaskId ASSTAPI AsstAppendTask(AsstHandle /*handle*/, const char* /*type*/, const char* /*params*/) { return 1; }
AsstBool  ASSTAPI AsstSetTaskParams(AsstHandle /*handle*/, AsstTaskId /*id*/, const char* /*params*/) { return 1; }

AsstBool ASSTAPI AsstStart(AsstHandle /*handle*/) { return 1; }
AsstBool ASSTAPI AsstStop(AsstHandle /*handle*/) { return 1; }
AsstBool ASSTAPI AsstRunning(AsstHandle /*handle*/) { return 0; }
AsstBool ASSTAPI AsstConnected(AsstHandle /*handle*/) { return 0; }
AsstBool ASSTAPI AsstBackToHome(AsstHandle /*handle*/) { return 1; }

AsstAsyncCallId ASSTAPI AsstAsyncConnect(AsstHandle /*handle*/, const char* /*adb_path*/, const char* /*address*/, const char* /*config*/, AsstBool /*block*/) { return 1; }
void ASSTAPI AsstSetConnectionExtras(const char* /*name*/, const char* /*extras*/) { }

AsstAsyncCallId ASSTAPI AsstAsyncClick(AsstHandle /*handle*/, int32_t /*x*/, int32_t /*y*/, AsstBool /*block*/) { return 1; }
AsstAsyncCallId ASSTAPI AsstAsyncScreencap(AsstHandle /*handle*/, AsstBool /*block*/) { return 1; }

AsstSize ASSTAPI AsstGetImage(AsstHandle /*handle*/, void* /*buff*/, AsstSize /*buff_size*/) { return 0; }
AsstSize ASSTAPI AsstGetImageBgr(AsstHandle /*handle*/, void* /*buff*/, AsstSize /*buff_size*/) { return 0; }
AsstSize ASSTAPI AsstGetUUID(AsstHandle /*handle*/, char* buff, AsstSize buff_size) {
    const char* u = "stub-uuid";
    size_t n = strlen(u);
    if (!buff || buff_size == 0) return n + 1; // indicate required size
    size_t to_copy = (n + 1 < buff_size) ? n + 1 : buff_size;
    memcpy(buff, u, to_copy);
    return (AsstSize)to_copy;
}
AsstSize ASSTAPI AsstGetTasksList(AsstHandle /*handle*/, AsstTaskId* /*buff*/, AsstSize /*buff_size*/) { return 0; }
AsstSize ASSTAPI AsstGetNullSize() { return (AsstSize)-1; }

const char* ASST_CALL AsstGetVersion() { return kVer; }
void ASSTAPI AsstLog(const char* /*level*/, const char* /*message*/) {}

} // extern "C"
EOF

RUN stitch_libafl_cxx -O2 -fPIC -I/fuzz/install/include -c /fuzz/build/maa_stub.cpp -o /fuzz/build/maa_stub.o \
 && ar rcs /fuzz/install/lib/libMaaCore.a /fuzz/build/maa_stub.o \
 && ranlib /fuzz/install/lib/libMaaCore.a
