#include <cstdio>
#include <cstring>
#include <aspell.h>

int main() {
    AspellConfig * cfg = new_aspell_config();
    if (!cfg) {
        return 1;
    }
    // Set some basic options that don't require dictionaries
    aspell_config_replace(cfg, "encoding", "utf-8");
    aspell_config_replace(cfg, "lang", "en");

    // Retrieve a value back
    const char *enc = aspell_config_retrieve(cfg, "encoding");
    if (!enc || std::strcmp(enc, "utf-8") != 0) {
        delete_aspell_config(cfg);
        return 2;
    }

    // Enumerate possible elements to exercise API
    AspellKeyInfoEnumeration * en = aspell_config_possible_elements(cfg, 0);
    // Just iterate a few entries if any
    int count = 0;
    for (; !aspell_key_info_enumeration_at_end(en) && count < 3; ++count) {
        const AspellKeyInfo * ki = aspell_key_info_enumeration_next(en);
        (void)ki;
    }
    delete_aspell_key_info_enumeration(en);

    delete_aspell_config(cfg);
    std::printf("OK %d\n", count);
    return 0;
}
