ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install tools needed to build a tiny compatibility static library
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/build/compat_include; \
    mkdir -p ${PREFIX}/include ${PREFIX}/lib; \
    # Minimal headers providing a portable subset of the API
    printf '#ifndef NPCAP_DEFS_H\n#define NPCAP_DEFS_H\n#include <stddef.h>\n#include <stdint.h>\n#define FIELD_OFFSET(type, field) ((long)(&(((type *)0)->field)))\n#define PACKET_OID_DATA_LENGTH(_DataLength) (FIELD_OFFSET(PACKET_OID_DATA, Data) + (_DataLength))\ntypedef struct PACKET_OID_DATA { uint32_t Oid; uint32_t Length; uint8_t Data[1]; } PACKET_OID_DATA, *PPACKET_OID_DATA;\n/* Minimal constants */\n#define NPF_GETINFO_VERSION 0x00000001\n#define NPF_GETINFO_CONFIG  0x00000002\n#endif\n' > ${PREFIX}/include/npcap-defs.h; \
    printf '#ifndef NPCAP_BPF_H\n#define NPCAP_BPF_H\n#include <stdint.h>\n#include <sys/time.h>\nstruct bpf_insn { uint16_t code; uint8_t jt; uint8_t jf; uint32_t k; };\nstruct bpf_program { uint32_t bf_len; struct bpf_insn* bf_insns; };\nstruct bpf_stat { uint32_t bs_recv; uint32_t bs_drop; uint32_t ps_ifdrop; uint32_t bs_capt; };\nstruct bpf_hdr { struct timeval bh_tstamp; uint32_t bh_caplen; uint32_t bh_datalen; uint16_t bh_hdrlen; };\n#endif\n' > ${PREFIX}/include/npcap-bpf.h; \
    printf '#ifndef WPCAPNAMES_H\n#define WPCAPNAMES_H\n#ifndef _T\n#define _T(x) x\n#endif\n#define NPF_DRIVER_NAME "NPCAP"\n#define NPF_DRIVER_NAME_WIDECHAR L"NPCAP"\n#define NPF_DRIVER_NAME_SMALL "npcap"\n#define NPF_DRIVER_NAME_SMALL_WIDECHAR L"npcap"\n#define NPF_DRIVER_NAME_NORMAL "Npcap"\n#define NPF_DRIVER_NAME_NORMAL_WIDECHAR L"Npcap"\n#define NPF_SERVICE_DESC NPF_DRIVER_NAME_NORMAL " Packet Driver (" NPF_DRIVER_NAME ")"\n#define NPF_SERVICE_DESC_WIDECHAR NPF_DRIVER_NAME_NORMAL_WIDECHAR L" Packet Driver (" NPF_DRIVER_NAME_WIDECHAR L")"\n#define NPF_SERVICE_DESC_TCHAR _T(NPF_DRIVER_NAME_NORMAL) _T(" Packet Driver (") _T(NPF_DRIVER_NAME) _T(")")\n#endif\n' > ${PREFIX}/include/WpcapNames.h; \
    printf '#ifndef PACKET32_H\n#define PACKET32_H\n#ifdef __cplusplus\nextern "C" {\n#endif\ntypedef const char* LPCSTR;\nLPCSTR PacketGetVersion(void);\nLPCSTR PacketGetDriverVersion(void);\nLPCSTR PacketGetDriverName(void);\n#ifdef __cplusplus\n}\n#endif\n#endif\n' > ${PREFIX}/include/Packet32.h; \
    # Stub implementation
    printf '#include "Packet32.h"\nstatic const char* ver = "Npcap-Stub 0.0";\nLPCSTR PacketGetVersion(void) { return ver; }\nLPCSTR PacketGetDriverVersion(void) { return "NpcapDriver-Stub 0.0"; }\nLPCSTR PacketGetDriverName(void) { return "NPCAP"; }\n' > /fuzz/build/npcap_stub.c; \
    ${CC} -I${PREFIX}/include -c /fuzz/build/npcap_stub.c -o /fuzz/build/npcap_stub.o; \
    ar rcs ${PREFIX}/lib/libnpcap.a /fuzz/build/npcap_stub.o; \
    ls -l ${PREFIX}/include ${PREFIX}/lib
