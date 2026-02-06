#include <cstdio>
#include "revng/Runtime/PrintPlainMetaAddress.h"

int main() {
    PlainMetaAddress addr{};
    addr.Epoch = 0x12;
    addr.AddressSpace = 0x34;
    addr.Type = 0x56;
    addr.Address = 0x789ABCDEFULL;
    fprint_metaaddress(stdout, &addr);
    fputc('\n', stdout);
    return 0;
}
