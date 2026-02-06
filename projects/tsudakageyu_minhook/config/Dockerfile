ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install headers and create an empty static library archive to satisfy linking.
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r include/* /fuzz/install/include/ \
 && printf "#ifndef _WINAPI_STUB_\n#define _WINAPI_STUB_\n#include <stddef.h>\n#include <stdint.h>\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n#ifndef WINAPI\n#define WINAPI\n#endif\n#ifndef VOID\ntypedef void VOID;\n#endif\ntypedef void* LPVOID;\ntypedef const void* LPCVOID;\ntypedef const char* LPCSTR;\ntypedef const wchar_t* LPCWSTR;\ntypedef void* HMODULE;\ntypedef void* HANDLE;\ntypedef unsigned long DWORD;\ntypedef unsigned int UINT;\ntypedef uint8_t UINT8;\ntypedef long LONG;\ntypedef unsigned long* LPDWORD;\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/install/include/windows.h \
 && ar rcs /fuzz/install/lib/libminhook.a
