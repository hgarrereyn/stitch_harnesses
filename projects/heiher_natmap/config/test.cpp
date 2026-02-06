#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
const char *hev_conf_help(void);
#ifdef __cplusplus
}
#endif

int main() {
    const char *help = hev_conf_help();
    if (help) {
        const char *nl = help;
        while (*nl && *nl != '\n') nl++;
        fwrite(help, 1, nl - help, stdout);
        fputc('\n', stdout);
    } else {
        puts("no help text");
    }
    return 0;
}
