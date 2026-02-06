#include <cstdio>
#include <cstring>
extern "C" {
#include <putty/misc.h>
#include <putty/tree234.h>
}

static int intcmp(void *av, void *bv) {
    int a = *(int*)av;
    int b = *(int*)bv;
    return (a > b) - (a < b);
}

int main() {
    // Test base64 encode/decode via misc.h API
    const char *msg = "hello world";
    ptrlen in = make_ptrlen(msg, strlen(msg));
    strbuf *enc = base64_encode_sb(in, 0); // single line
    if (enc->len == 0) return 1;

    strbuf *dec = base64_decode_sb(make_ptrlen(enc->s, enc->len));
    bool ok = (dec->len == strlen(msg)) && (memcmp(dec->s, msg, dec->len) == 0);

    strbuf_free(enc);
    strbuf_free(dec);

    // Exercise tree234 API
    tree234 *t = newtree234(intcmp);
    int a=3,b=1,c=2;
    add234(t, &a);
    add234(t, &b);
    add234(t, &c);
    if (count234(t) != 3) return 2;
    int *p = (int*)index234(t, 0);
    int *q = (int*)index234(t, 1);
    int *r = (int*)index234(t, 2);
    if (!p || !q || !r) return 3;
    if (!(*p==1 && *q==2 && *r==3)) return 4;
    freetree234(t);

    return ok ? 0 : 5;
}
