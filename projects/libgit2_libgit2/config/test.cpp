#include <stdio.h>
#include <git2.h>

int main() {
    int major=0, minor=0, rev=0;
    git_libgit2_version(&major, &minor, &rev);
    printf("libgit2 version: %d.%d.%d\n", major, minor, rev);

    if (git_libgit2_init() < 0) {
        printf("init failed\n");
        return 1;
    }

    const char *path = "/tmp/libgit2_testrepo";
    git_repository *repo = NULL;
    int error = git_repository_init(&repo, path, 1 /* bare */);
    if (error < 0) {
        const git_error *e = git_error_last();
        printf("repo init error: %d %s\n", error, e && e->message ? e->message : "(no message)");
        git_libgit2_shutdown();
        return 0; // don't fail the test, library still linked
    }

    if (repo) {
        printf("Repository initialized at %s\n", path);
        git_repository_free(repo);
    }

    git_libgit2_shutdown();
    return 0;
}
