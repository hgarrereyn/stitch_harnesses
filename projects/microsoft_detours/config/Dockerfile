ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/src/detours.h /fuzz/install/include/ && \
    cp /fuzz/src/src/detver.h /fuzz/install/include/

# winver.h stub for detver.h
RUN bash -lc "printf '%s\n' '#ifndef _WINVER_H_' '#define _WINVER_H_ 1' '#endif' > /fuzz/install/include/winver.h"

# Compatibility shim header to make detours.h usable on Linux
RUN bash -lc "printf '%s\n' \
'#ifndef DETOURS_COMPAT_H' \
'#define DETOURS_COMPAT_H' \
'/* Force a known architecture so detours.h does not error out */' \
'#ifndef _AMD64_' \
'#define _AMD64_ 1' \
'#endif' \
'#ifndef _WIN64' \
'#define _WIN64 1' \
'#endif' \
'/* Basic Windows-style types */' \
'typedef unsigned char BYTE;' \
'typedef BYTE* PBYTE;' \
'typedef const BYTE* LPCBYTE;' \
'typedef unsigned short WORD;' \
'typedef unsigned int UINT;' \
'typedef int INT;' \
'typedef unsigned long DWORD;' \
'typedef long LONG;' \
'typedef unsigned long ULONG;' \
'typedef int BOOL;' \
'typedef void VOID;' \
'typedef void* PVOID;' \
'typedef void* LPVOID;' \
'typedef const void* LPCVOID;' \
'typedef const char* LPCSTR;' \
'typedef const wchar_t* LPCWSTR;' \
'typedef char* LPSTR;' \
'typedef wchar_t* LPWSTR;' \
'typedef char CHAR;' \
'typedef void* HANDLE;' \
'typedef void* HMODULE;' \
'typedef void* HWND;' \
'typedef void* HINSTANCE;' \
'typedef unsigned short USHORT;' \
'typedef unsigned long* PDWORD;' \
'#ifndef TRUE' \
'#define TRUE 1' \
'#endif' \
'#ifndef FALSE' \
'#define FALSE 0' \
'#endif' \
'#ifndef NULL' \
'#define NULL ((void*)0)' \
'#endif' \
'#ifndef CALLBACK' \
'#define CALLBACK' \
'#endif' \
'#ifndef WINAPI' \
'#define WINAPI' \
'#endif' \
'/* SAL macros no-ops */' \
'#ifndef _Out_' \
'#define _Out_' \
'#endif' \
'#ifndef _Out_opt_' \
'#define _Out_opt_' \
'#endif' \
'#ifndef _Out_writes_' \
'#define _Out_writes_(x)' \
'#endif' \
'#ifndef _In_' \
'#define _In_' \
'#endif' \
'#ifndef _In_opt_' \
'#define _In_opt_' \
'#endif' \
'#ifndef _Inout_' \
'#define _Inout_' \
'#endif' \
'#ifndef _Inout_opt_' \
'#define _Inout_opt_' \
'#endif' \
'#ifndef _Readable_bytes_' \
'#define _Readable_bytes_(x)' \
'#endif' \
'#ifndef _Writable_bytes_' \
'#define _Writable_bytes_(x)' \
'#endif' \
'#ifndef _Outptr_result_maybenull_' \
'#define _Outptr_result_maybenull_' \
'#endif' \
'/* Minimal PE-related structs */' \
'typedef struct _IMAGE_DATA_DIRECTORY { DWORD VirtualAddress; DWORD Size; } IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;' \
'typedef struct _IMAGE_DOS_HEADER { WORD e_magic; } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;' \
'typedef struct _IMAGE_SECTION_HEADER { BYTE dummy[40]; } IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;' \
'typedef struct _IMAGE_NT_HEADERS { char _pad[0x108]; } IMAGE_NT_HEADERS, *PIMAGE_NT_HEADERS;' \
'/* Process/thread related placeholders */' \
'typedef struct _SECURITY_ATTRIBUTES { DWORD nLength; LPVOID lpSecurityDescriptor; BOOL bInheritHandle; } SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;' \
'typedef struct _STARTUPINFOA { DWORD cb; LPSTR lpReserved; LPSTR lpDesktop; LPSTR lpTitle; DWORD dwFlags; WORD wShowWindow; WORD cbReserved2; unsigned char* lpReserved2; HANDLE hStdInput; HANDLE hStdOutput; HANDLE hStdError; } STARTUPINFOA, *LPSTARTUPINFOA;' \
'typedef struct _STARTUPINFOW { DWORD cb; LPWSTR lpReserved; LPWSTR lpDesktop; LPWSTR lpTitle; DWORD dwFlags; WORD wShowWindow; WORD cbReserved2; unsigned char* lpReserved2; HANDLE hStdInput; HANDLE hStdOutput; HANDLE hStdError; } STARTUPINFOW, *LPSTARTUPINFOW;' \
'typedef struct _PROCESS_INFORMATION { HANDLE hProcess; HANDLE hThread; DWORD dwProcessId; DWORD dwThreadId; } PROCESS_INFORMATION, *LPPROCESS_INFORMATION;' \
'/* Define C_ASSERT for use in detours.h (no-op) */' \
'#ifndef C_ASSERT' \
'#define C_ASSERT(x)' \
'#endif' \
'#include <detours.h>' \
'#endif' > /fuzz/install/include/detours_compat.h"

# Create a tiny static library stub so linking succeeds
RUN bash -lc 'echo "void __detours_dummy(void){}" > /tmp/dummy.c && \
    gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libdetours.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o'

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install
