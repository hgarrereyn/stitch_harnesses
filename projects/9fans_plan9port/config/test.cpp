#include <stdio.h>
#include <string.h>
#include <utf.h>

int main(){
    const char *s = "hello, 世界"; // UTF-8 string
    int nbytes = (int)strlen(s);
    int nchars = utflen((char*)s);
    printf("bytes=%d, runes=%d\n", nbytes, nchars);

    Rune r;
    char buf[8] = {0};
    int c = chartorune(&r, (char*)s);
    int out = runetochar(buf, &r);
    printf("first rune bytes in: %d, out: %d, codepoint: U+%04X, as utf8: %s\n", c, out, r, buf);
    return 0;
}
