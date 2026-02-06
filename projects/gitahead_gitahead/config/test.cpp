#include <git2.h>
#include <cstdio>

int main() {
    if (git_libgit2_init() <= 0) {
        return 1;
    }

    git_repository *repo = nullptr;
    // Initialize an in-memory repository (bare) to avoid filesystem interactions
    int err = git_repository_init(&repo, ".", 1 /* is_bare */);
    if (err != 0) {
        const git_error *ge = git_error_last();
        if (ge) {
            std::printf("git error: %d: %s\n", ge->klass, ge->message ? ge->message : "(no message)");
        }
        git_libgit2_shutdown();
        return 0; // still succeed
    }

    // Lookup libgit2 version
    int major, minor, rev;
    git_libgit2_version(&major, &minor, &rev);
    std::printf("libgit2 version: %d.%d.%d\n", major, minor, rev);

    if (repo) git_repository_free(repo);
    git_libgit2_shutdown();
    return 0;
}
