#include <stdio.h>
#include <string.h>
#include "llhttp.h"

static int on_message_complete(llhttp_t* parser) {
    (void)parser;
    fprintf(stdout, "Message completed!\n");
    return 0;
}

int main() {
    llhttp_t parser;
    llhttp_settings_t settings;

    llhttp_settings_init(&settings);
    settings.on_message_complete = on_message_complete;

    llhttp_init(&parser, HTTP_BOTH, &settings);

    const char* request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    enum llhttp_errno err = llhttp_execute(&parser, request, (size_t)strlen(request));
    if (err == HPE_OK) {
        printf("Successfully parsed! HTTP/%d.%d\n", llhttp_get_http_major(&parser), llhttp_get_http_minor(&parser));
        return 0;
    } else {
        fprintf(stderr, "Parse error: %s %s\n", llhttp_errno_name(err), llhttp_get_error_reason(&parser));
        return 1;
    }
}
