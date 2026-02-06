#include <stdio.h>
#include <string.h>
#include <uriparser/Uri.h>

int main() {
    const char *text = "https://example.com:8080/path/to/resource?x=1&y=2#frag";

    UriParserStateA state;
    UriUriA uri;
    memset(&uri, 0, sizeof(uri));
    state.uri = &uri;

    if (uriParseUriA(&state, text) != URI_SUCCESS) {
        fprintf(stderr, "uriParseUriA failed: errorPos=%ld\n", (long)(state.errorPos - text));
        uriFreeUriMembersA(&uri);
        return 1;
    }

    // Convert URI back to string
    int needed = 0;
    if (uriToStringCharsRequiredA(&uri, &needed) == URI_SUCCESS) {
        char buf[1024];
        if (needed + 1 < (int)sizeof(buf)) {
            int written = 0;
            if (uriToStringA(buf, &uri, sizeof(buf), &written) == URI_SUCCESS) {
                printf("ToString: %s (written=%d)\n", buf, written);
            }
        }
    }

    // Simple use of query iteration API
    UriQueryListA *queryList = NULL;
    int itemCount = 0;
    if (uriDissectQueryMallocA(&queryList, &itemCount, uri.query.first, uri.query.afterLast) == URI_SUCCESS) {
        printf("Query items: %d\n", itemCount);
        const UriQueryListA *p = queryList;
        while (p) {
            printf("%s=%s\n", p->key ? p->key : "", p->value ? p->value : "");
            p = p->next;
        }
        uriFreeQueryListA(queryList);
    }

    uriFreeUriMembersA(&uri);
    return 0;
}
