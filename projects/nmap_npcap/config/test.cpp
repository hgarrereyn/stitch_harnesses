#include <cstdio>
#include "Packet32.h"
int main(){
    const char* v = PacketGetVersion();
    std::printf("Npcap version: %s\n", v ? v : "(null)");
    return 0;
}
