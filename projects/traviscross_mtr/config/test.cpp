#include <stdio.h>
#include <string.h>
#include <sys/time.h>
extern "C" {
#include "cmdparse.h"
#include "timeval.h"
}

int main() {
    // Test parse_command
    struct command_t cmd; 
    memset(&cmd, 0, sizeof(cmd));
    char buf[] = "1 probe ip=4 host=example.com ttl=3";
    int r = parse_command(&cmd, buf);
    printf("parse_command ret=%d token=%d name=%s argc=%d\n", r, cmd.token, cmd.command_name ? cmd.command_name : "(null)", cmd.argument_count);

    // Test timeval helpers
    struct timeval a = { .tv_sec = 1, .tv_usec = 1500000 };
    normalize_timeval(&a);
    struct timeval b = { .tv_sec = 2, .tv_usec = 1000 };
    int cmp = compare_timeval(a, b);
    printf("compare_timeval=%d a=%ld.%06ld b=%ld.%06ld\n", cmp, (long)a.tv_sec, (long)a.tv_usec, (long)b.tv_sec, (long)b.tv_usec);
    return 0;
}
