ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/install/include && cp -r /fuzz/src/include/* /fuzz/install/include/

RUN cat > /fuzz/install/include/lav_compat.h <<'EOF'
#ifndef LAV_COMPAT_H
#define LAV_COMPAT_H
#include <stdint.h>
#include <stddef.h>
// Basic Windows/COM type substitutes
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned long DWORD_PTR;
typedef long HRESULT;
typedef char CHAR;
typedef float FLOAT;
typedef wchar_t WCHAR;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef wchar_t* LPWSTR;
typedef const wchar_t* LPCWSTR;
typedef const wchar_t* LPCOLESTR;
typedef wchar_t* BSTR;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
typedef LONGLONG REFERENCE_TIME;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
// GUID structure and helpers
typedef struct _GUID {
  uint32_t Data1;
  uint16_t Data2;
  uint16_t Data3;
  uint8_t  Data4[8];
} GUID;
#ifndef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1,b2,b3,b4,b5,b6,b7,b8) \
  static const GUID name = { (uint32_t)(l), (uint16_t)(w1), (uint16_t)(w2), \
    { (uint8_t)(b1), (uint8_t)(b2), (uint8_t)(b3), (uint8_t)(b4), (uint8_t)(b5), (uint8_t)(b6), (uint8_t)(b7), (uint8_t)(b8) } }
#endif

// Minimal COM-like macros to make interfaces compile
#ifndef __declspec
#define __declspec(x)
#endif
#ifndef interface
#define interface struct
#endif
#ifndef STDMETHOD
#define STDMETHOD(method) virtual HRESULT method
#endif
#ifndef STDMETHOD_
#define STDMETHOD_(type, method) virtual type method
#endif
#ifndef PURE
#define PURE = 0
#endif
#ifndef STDMETHODCALLTYPE
#define STDMETHODCALLTYPE
#endif

// Minimal IUnknown definition
struct IUnknown { virtual ~IUnknown() {} };

#endif // LAV_COMPAT_H
EOF

# Minimal shims for Windows SDK headers referenced by LAV headers
RUN printf "#pragma once\n#include \"lav_compat.h\"\n" > /fuzz/install/include/Unknwn.h
RUN cat > /fuzz/install/include/OCIdl.h <<'EOF'
#pragma once
#include "lav_compat.h"
struct IPropertyPage; // forward decl
interface ISpecifyPropertyPages : public IUnknown { virtual ~ISpecifyPropertyPages() {} };
EOF
