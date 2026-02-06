#include <iostream>
extern "C" {
#include <nokogiri_gumbo.h>
}

// Simple recursive traversal to count nodes
static size_t count_nodes(GumboNode* node) {
    if (!node) return 0;
    size_t count = 1; // count this node
    if (node->type == GUMBO_NODE_ELEMENT || node->type == GUMBO_NODE_DOCUMENT || node->type == GUMBO_NODE_TEMPLATE) {
        GumboVector children = (node->type == GUMBO_NODE_ELEMENT || node->type == GUMBO_NODE_TEMPLATE)
            ? node->v.element.children
            : node->v.document.children;
        for (unsigned int i = 0; i < children.length; ++i) {
            count += count_nodes(static_cast<GumboNode*>(children.data[i]));
        }
    }
    return count;
}

int main() {
    const char* html = "<html><head><title>T</title></head><body><p id='x'>Hello <b>world</b>!</p></body></html>";
    GumboOutput* output = gumbo_parse(html);
    if (!output || !output->root) {
        std::cerr << "Failed to parse HTML" << std::endl;
        return 1;
    }
    size_t total = count_nodes(output->document);
    std::cout << "Parsed nodes: " << total << " status=" << gumbo_status_to_string(output->status) << std::endl;
    gumbo_destroy_output(output);
    return 0;
}
