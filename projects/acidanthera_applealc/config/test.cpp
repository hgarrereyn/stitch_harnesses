#include <stdio.h>
#include <UserKernelShared.h>

int main() {
    // Just exercise the public enum to ensure header is usable
    int methods = kNumberOfMethods;
    printf("AppleALC User/Kernel shared methods: %d\n", methods);
    return 0;
}
