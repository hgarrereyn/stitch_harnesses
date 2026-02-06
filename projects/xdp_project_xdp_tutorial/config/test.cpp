#include <stdio.h>
#include <bpf/libbpf.h>

int main() {
    int n = libbpf_num_possible_cpus();
    printf("libbpf_num_possible_cpus: %d\n", n);
    return 0;
}
