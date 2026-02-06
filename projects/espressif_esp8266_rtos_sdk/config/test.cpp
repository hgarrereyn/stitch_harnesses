#include <stdio.h>
#include <string.h>
#include <http_parser.h>

static int on_url(http_parser* p, const char* at, size_t length) {
    (void)p;
    printf("URL: %.*s\n", (int)length, at);
    return 0;
}

static int on_header_field(http_parser* p, const char* at, size_t length) {
    (void)p;
    printf("H: %.*s: ", (int)length, at);
    return 0;
}

static int on_header_value(http_parser* p, const char* at, size_t length) {
    (void)p;
    printf("%.*s\n", (int)length, at);
    return 0;
}

static int on_body(http_parser* p, const char* at, size_t length) {
    (void)p;
    printf("Body: %.*s\n", (int)length, at);
    return 0;
}

int main() {
    const char* req =
        "GET /path/resource?x=1 HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "User-Agent: test\r\n"
        "Accept: */*\r\n"
        "\r\n";

    http_parser_settings settings;
    memset(&settings, 0, sizeof(settings));
    settings.on_url = on_url;
    settings.on_header_field = on_header_field;
    settings.on_header_value = on_header_value;
    settings.on_body = on_body;

    http_parser parser;
    http_parser_init(&parser, HTTP_REQUEST);

    size_t nparsed = http_parser_execute(&parser, &settings, req, strlen(req));

    if (nparsed != strlen(req) || HTTP_PARSER_ERRNO(&parser) != HPE_OK) {
        fprintf(stderr, "Parse error: %s at %zu/%zu\n", http_errno_description(HTTP_PARSER_ERRNO(&parser)), nparsed, strlen(req));
        return 1;
    }
    printf("Parsed OK\n");
    return 0;
}
