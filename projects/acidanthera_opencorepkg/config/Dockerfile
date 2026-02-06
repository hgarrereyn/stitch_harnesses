ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build; cp -r /fuzz/src/Include/* /fuzz/install/include/ || true; mkdir -p /fuzz/install/include/Library /fuzz/install/include/Protocol

RUN cat > /fuzz/install/include/Base.h <<'EOF'
#ifndef EDK2_BASE_SHIM
#define EDK2_BASE_SHIM
#include <stdint.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef uint8_t  UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef int32_t  INT32;
typedef size_t   UINTN;
typedef char     CHAR8;
typedef uint16_t CHAR16;
typedef uint8_t  BOOLEAN;
typedef UINT64   EFI_STATUS;
typedef void*    EFI_HANDLE;
struct EFI_DEVICE_PATH_PROTOCOL_;
typedef struct EFI_DEVICE_PATH_PROTOCOL_ EFI_DEVICE_PATH_PROTOCOL;
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef CONST
#define CONST const
#endif
#ifndef VOID
#define VOID void
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif
#ifndef EFIAPI
#define EFIAPI
#endif
#ifdef __cplusplus
}
#endif
#endif
EOF

RUN cat > /fuzz/install/include/Library/BaseMemoryLib.h <<'EOF'
#pragma once
#include <Base.h>
#include <string.h>
static inline void *CopyMem(void *Dest, const void *Src, UINTN Len){ return memcpy(Dest, Src, Len);} 
static inline void ZeroMem(void *Dest, UINTN Len){ memset(Dest, 0, Len);} 
EOF

RUN cat > /fuzz/install/include/Library/BaseOverflowLib.h <<'EOF'
#pragma once
#include <Base.h>
EOF

RUN cat > /fuzz/install/include/Library/DebugLib.h <<'EOF'
#pragma once
#include <Base.h>
EOF

RUN cat > /fuzz/install/include/Protocol/AudioIo.h <<'EOF'
#pragma once
#include <Base.h>
typedef enum { EfiAudioIoFreq8kHz, EfiAudioIoFreq11kHz, EfiAudioIoFreq16kHz, EfiAudioIoFreq22kHz, EfiAudioIoFreq32kHz, EfiAudioIoFreq44kHz, EfiAudioIoFreq48kHz, EfiAudioIoFreq88kHz, EfiAudioIoFreq96kHz, EfiAudioIoFreq192kHz } EFI_AUDIO_IO_PROTOCOL_FREQ;
typedef enum { EfiAudioIoBits8, EfiAudioIoBits16, EfiAudioIoBits20, EfiAudioIoBits24, EfiAudioIoBits32 } EFI_AUDIO_IO_PROTOCOL_BITS;
EOF

RUN cat > /tmp/build/ocxml_stub.cpp <<'EOF'
#include <Acidanthera/Library/OcXmlLib.h>
#include <stdlib.h>
struct XML_DOCUMENT_ { int dummy; };
struct XML_NODE_ { int dummy; };
XML_DOCUMENT * XmlDocumentParse(CHAR8 *Buffer, UINT32 Length, BOOLEAN WithRefs){ (void)Buffer; (void)Length; (void)WithRefs; return (XML_DOCUMENT*)malloc(sizeof(XML_DOCUMENT)); }
CHAR8 * XmlDocumentExport(const XML_DOCUMENT *Document, UINT32 *Length, UINT32 Skip, BOOLEAN Prepend){ (void)Document; (void)Skip; (void)Prepend; if (Length) *Length = 0; CHAR8 *s=(CHAR8*)malloc(1); if (s) s[0]=0; return s; }
void XmlDocumentFree(XML_DOCUMENT *Document){ free(Document);} 
XML_NODE * XmlDocumentRoot(const XML_DOCUMENT *Document){ (void)Document; return (XML_NODE*)0; }
const CHAR8 * XmlNodeName(const XML_NODE *Node){ (void)Node; return (const CHAR8*)""; }
const CHAR8 * XmlNodeContent(const XML_NODE *Node){ (void)Node; return (const CHAR8*)0; }
EOF

RUN stitch_libafl_cxx -fPIC -I/fuzz/install/include -c /tmp/build/ocxml_stub.cpp -o /tmp/build/ocxml_stub.o && ar rcs /fuzz/install/lib/libocxmlstub.a /tmp/build/ocxml_stub.o && rm -rf /tmp/build

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
