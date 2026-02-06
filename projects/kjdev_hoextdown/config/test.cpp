#include <cstdio>
#include <cstring>
#include <hoedown/html.h>

int main() {
    const char *md = "# Header 1\n\n- [x] task done\n\nThis is a paragraph. {@paragraph #pid}\n";
    hoedown_buffer *out = hoedown_buffer_new(64);
    hoedown_renderer *renderer = hoedown_html_renderer_new((hoedown_html_flags)(HOEDOWN_HTML_USE_TASK_LIST | HOEDOWN_HTML_HEADER_ID), 0);
    hoedown_document *doc = hoedown_document_new(renderer,
        (hoedown_extensions)(HOEDOWN_EXT_BLOCK | HOEDOWN_EXT_SPAN | HOEDOWN_EXT_FLAGS),
        16, 0, NULL, NULL);
    hoedown_document_render(doc, out, (const uint8_t*)md, strlen(md));
    if (out && out->data && out->size > 0) {
        fwrite(out->data, 1, out->size, stdout);
    }
    hoedown_document_free(doc);
    hoedown_html_renderer_free(renderer);
    hoedown_buffer_free(out);
    return 0;
}
