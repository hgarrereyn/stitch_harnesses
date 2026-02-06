#include <cstdio>
#include <hwloc.h>

int main() {
    hwloc_topology_t topo;
    if (hwloc_topology_init(&topo) != 0) {
        printf("init failed\n");
        return 1;
    }
    if (hwloc_topology_load(topo) != 0) {
        printf("load failed\n");
        hwloc_topology_destroy(topo);
        return 1;
    }
    int depth = hwloc_topology_get_depth(topo);
    printf("hwloc topology depth: %d\n", depth);
    int pu_depth = hwloc_get_type_depth(topo, HWLOC_OBJ_PU);
    unsigned nbpus = hwloc_get_nbobjs_by_depth(topo, pu_depth);
    printf("number of PUs: %u\n", nbpus);
    hwloc_topology_destroy(topo);
    return 0;
}
