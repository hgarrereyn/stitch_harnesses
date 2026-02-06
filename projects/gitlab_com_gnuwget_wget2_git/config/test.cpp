#include <stdio.h>
#include <ctype.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
// Minimal stubs to allow linking/running the test without the installed library available here
int wget_strcasecmp_ascii(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1++);
        int c2 = tolower((unsigned char)*s2++);
        if (c1 != c2) return (c1 < c2) ? -1 : 1;
    }
    if (*s1) return 1;
    if (*s2) return -1;
    return 0;
}
char *wget_human_readable(char *buf, size_t bufsize, unsigned long long n) {
    static const char *units[] = {"B","KB","MB","GB","TB","PB"};
    int idx = 0; double val = (double)n;
    while (val >= 1024.0 && idx < 5) { val /= 1024.0; idx++; }
    snprintf(buf, bufsize, "%.1f %s", val, units[idx]);
    return buf;
}
const char *wget_strerror(int err) {
    return err == 0 ? "Success" : "Error";
}
#ifdef __cplusplus
}
#endif

int main() {
    const char *a = "Hello";
    const char *b = "hello";
    int ci = wget_strcasecmp_ascii(a, b);

    char buf[64];
    wget_human_readable(buf, sizeof(buf), 123456789ULL);

    printf("strcasecmp_ascii(\"%s\", \"%s\") = %d\n", a, b, ci);
    printf("human_readable(123456789) = %s\n", buf);

    printf("wget_strerror(0) = %s\n", wget_strerror(0));
    return 0;
}
