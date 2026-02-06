#include <cstdio>
#include <cstdlib>
#include <cstdint>
extern "C" {
#include <mfsio.h>
}

int main() {
    // Use API parts that do not require an initialized connection
    mfscfg cfg{};
    mfs_set_defaults(&cfg);

    mfsacl* acl = mfs_acl_alloc(2);
    if (!acl) {
        std::printf("mfs_acl_alloc failed\n");
        return 1;
    }
    acl->userperm = ACL_PERM_R | ACL_PERM_W;
    acl->groupperm = ACL_PERM_R;

    mfs_acl_free(acl);

    std::printf("MooseFS libmfsio basic test OK\n");
    return 0;
}
