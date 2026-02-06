#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <plist/plist.h>

int main() {
    plist_t dict = plist_new_dict();
    plist_dict_set_item(dict, "hello", plist_new_string("world"));
    plist_dict_set_item(dict, "answer", plist_new_int(42));

    char* xml = NULL; uint32_t len = 0;
    plist_to_xml(dict, &xml, &len);
    if (xml && len > 0) {
        // Print a tiny prefix to ensure it worked
        fwrite(xml, 1, len > 60 ? 60 : len, stdout);
        fputc('\n', stdout);
    }

    free(xml);
    plist_free(dict);
    return 0;
}
