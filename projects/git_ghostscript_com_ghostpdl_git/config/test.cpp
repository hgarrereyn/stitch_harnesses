#include <ghostscript/iapi.h>
#include <ghostscript/ierrors.h>
#include <cstdio>

int main() {
    gsapi_revision_t rev{};
    int r = gsapi_revision(&rev, sizeof(rev));
    if (r < 0) return 1;
    std::printf("Ghostscript %s (rev %ld)\n", rev.product ? rev.product : "?", rev.revision);

    void* inst = nullptr;
    if (gsapi_new_instance(&inst, nullptr) >= 0 && inst) {
        gsapi_delete_instance(inst);
    }
    return 0;
}
