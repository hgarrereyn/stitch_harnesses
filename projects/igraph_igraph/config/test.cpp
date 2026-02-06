#include <cstdio>
#include <igraph/igraph.h>

int main() {
    const char* ver = nullptr;
    int maj=0, min=0, pat=0;
    igraph_version(&ver, &maj, &min, &pat);

    igraph_t g;
    if (igraph_ring(&g, 10, /*directed*/ 0, /*mutual*/ 0, /*circular*/ 1) != IGRAPH_SUCCESS) {
        std::printf("igraph_ring failed\n");
        return 1;
    }

    igraph_integer_t vcount = igraph_vcount(&g);
    igraph_integer_t ecount = igraph_ecount(&g);
    std::printf("igraph %s (%d.%d.%d) built OK. graph: |V|=%ld |E|=%ld\n", ver ? ver : "?", maj, min, pat, (long)vcount, (long)ecount);

    igraph_destroy(&g);
    return 0;
}
