ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    make gcc g++ pkg-config libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Install headers first
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp missing_ciphersuites.h sslscan.h /fuzz/install/include/

# Create shim source implementing a tiny subset of the API for testing/linking
RUN cat > shim.c <<'EOF'
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct _bs {
  unsigned char *buf;
  size_t size;
  size_t len;
} bs;

void bs_new(bs **out) {
  if (!out) return;
  *out = (bs*)calloc(1, sizeof(bs));
  if (*out) { (*out)->size = 256; (*out)->buf = (unsigned char*)malloc((*out)->size); (*out)->len = 0; }
}
void bs_free(bs **p) {
  if (!p || !*p) return;
  free((*p)->buf);
  free(*p);
  *p = NULL;
}
void bs_append_bytes(bs *b, unsigned char *data, size_t n) {
  if (!b || !data) return;
  if (b->len + n > b->size) { size_t ns = b->size ? b->size : 256; while (b->len + n > ns) ns *= 2; b->buf = (unsigned char*)realloc(b->buf, ns); b->size = ns; }
  memcpy(b->buf + b->len, data, n);
  b->len += n;
}
size_t bs_get_len(bs *b) { return b ? b->len : 0; }
unsigned char bs_get_byte(bs *b, size_t off) { return (b && off < b->len) ? b->buf[off] : 0; }

const char *getPrintableTLSName(unsigned int tls_version) {
  switch (tls_version) {
    case 0: return "TLSv1.0";
    case 1: return "TLSv1.1";
    case 2: return "TLSv1.2";
    case 3: return "TLSv1.3";
    default: return "UNKNOWN";
  }
}

int xml_to_stdout = 0;
char *RESET = ""; char *COL_RED = ""; char *COL_YELLOW = ""; char *COL_BLUE = ""; char *COL_GREEN = ""; char *COL_PURPLE = ""; char *COL_GREY = ""; char *COL_RED_BG = "";
const char *program_banner = "";
EOF

# Build the static library
RUN stitch_libafl_cc -c shim.c -o shim.o \
 && ar rcs /fuzz/install/lib/libsslscan.a shim.o

# Make sslscan.h self-contained and avoid duplicate symbol definitions
RUN set -eux; \
    awk 'BEGIN{printed=0} {print} /#include "missing_ciphersuites.h"/ && !printed { \
      print "#include <sys/types.h>\n#include <sys/socket.h>\n#include <netinet/in.h>\n#include <arpa/inet.h>\n#include <sys/time.h>\n#include <openssl/ssl.h>\n#include <openssl/ocsp.h>\n#include <openssl/x509.h>\n#include <openssl/x509v3.h>"; printed=1 }' /fuzz/install/include/sslscan.h > /fuzz/install/include/sslscan.h.tmp \
    && mv /fuzz/install/include/sslscan.h.tmp /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*RESET.*$/extern char *RESET;/' /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*COL_RED.*$/extern char *COL_RED;/' /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*COL_YELLOW.*$/extern char *COL_YELLOW;/' /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*COL_BLUE.*$/extern char *COL_BLUE;/' /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*COL_GREEN.*$/extern char *COL_GREEN;/' /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*COL_PURPLE.*$/extern char *COL_PURPLE;/' /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*COL_GREY.*$/extern char *COL_GREY;/' /fuzz/install/include/sslscan.h \
    && sed -E -i 's/^char \*COL_RED_BG.*$/extern char *COL_RED_BG;/' /fuzz/install/include/sslscan.h \
    && awk 'BEGIN{skip=0} /^const char \*program_banner/ { print "extern const char *program_banner;"; skip=1; next } skip { if ($0 ~ /";$/) { skip=0 } ; next } { print }' /fuzz/install/include/sslscan.h > /fuzz/install/include/sslscan.h.tmp \
    && mv /fuzz/install/include/sslscan.h.tmp /fuzz/install/include/sslscan.h \
    && awk '1; /#include "missing_ciphersuites.h"/ && !done { print "extern int xml_to_stdout;"; done=1 }' /fuzz/install/include/sslscan.h > /fuzz/install/include/sslscan.h.tmp2 \
    && mv /fuzz/install/include/sslscan.h.tmp2 /fuzz/install/include/sslscan.h

