#include <cstdio>
#include <ctime>
extern "C" {
#include <uwsgi.h>
}
int main() {
    char buf[128];
    time_t t = 0; // epoch
    int n = uwsgi_http_date(t, buf);
    if (n <= 0 || n >= (int)sizeof(buf)) return 1;
    buf[n] = '\0';
    printf("HTTP date: %s\n", buf);
    return 0;
}
