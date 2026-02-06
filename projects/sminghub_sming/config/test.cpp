#include <Sming/Core/Delegate.h>
#include <cstdio>

int main() {
    int acc = 0;
    Delegate<void(int)> cb = Delegate<void(int)>([&](int x){ acc += x; });
    cb(21);
    cb(21);
    printf("acc=%d\n", acc);
    return acc == 42 ? 0 : 1;
}
