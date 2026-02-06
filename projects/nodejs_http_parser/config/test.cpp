#include <iostream>
#include <cstring>
extern "C" {
#include <http_parser.h>
}

static int on_message_begin(http_parser*) { return 0; }
static int on_headers_complete(http_parser*) { return 0; }
static int on_message_complete(http_parser*) { return 0; }
static int on_url(http_parser*, const char*, size_t) { return 0; }
static int on_header_field(http_parser*, const char*, size_t) { return 0; }
static int on_header_value(http_parser*, const char*, size_t) { return 0; }
static int on_body(http_parser*, const char*, size_t) { return 0; }

int main() {
    const char* req =
        "GET /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "User-Agent: test\r\n"
        "Accept: */*\r\n"
        "\r\n";

    http_parser parser; 
    http_parser_settings settings{};
    settings.on_message_begin = on_message_begin;
    settings.on_headers_complete = on_headers_complete;
    settings.on_message_complete = on_message_complete;
    settings.on_url = on_url;
    settings.on_header_field = on_header_field;
    settings.on_header_value = on_header_value;
    settings.on_body = on_body;

    http_parser_init(&parser, HTTP_REQUEST);

    size_t nparsed = http_parser_execute(&parser, &settings, req, std::strlen(req));
    std::cout << "Parsed bytes: " << nparsed << " method=" << http_method_str((http_method)parser.method) << "\n";

    return 0;
}
