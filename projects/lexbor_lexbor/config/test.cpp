#include <stdio.h>
#include <string.h>
#include <lexbor/html/html.h>

static lxb_status_t noop_cb(const lxb_char_t *data, size_t len, void *ctx) {
    (void)ctx;
    fwrite(data, 1, len, stdout);
    return LXB_STATUS_OK;
}

int main() {
    const char *html = "<html><body><p>Hello Lexbor</p></body></html>";
    size_t html_len = strlen(html);

    lxb_html_document_t *document = lxb_html_document_create();
    if (document == NULL) {
        fprintf(stderr, "Failed to create document\n");
        return 1;
    }

    lxb_status_t status = lxb_html_document_parse(document, (const lxb_char_t*)html, html_len);
    if (status != LXB_STATUS_OK) {
        fprintf(stderr, "Parse failed: %d\n", (int)status);
        lxb_html_document_destroy(document);
        return 1;
    }

    // Serialize the DOM tree (pretty) to ensure symbols link correctly
    lxb_dom_node_t *root = lxb_dom_interface_node(document);
    lxb_html_serialize_pretty_tree_cb(root, LXB_HTML_SERIALIZE_OPT_UNDEF, 0, noop_cb, NULL);

    lxb_html_document_destroy(document);
    return 0;
}
