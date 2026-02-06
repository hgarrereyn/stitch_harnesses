#include <stdio.h>
#include <string.h>
extern "C" {
#include "common.h"
}

int main(){
    initPacketNodeList();
    WINDIVERT_ADDRESS addr; memset(&addr, 0, sizeof(addr));
    char data[4] = { 't','e','s','t' };
    PacketNode* n = createNode((char*)data, sizeof(data), &addr);
    appendNode(n);
    short c0 = calcChance(0);
    short c1 = calcChance(10000);
    popNode(n);
    freeNode(n);
    printf("ok %d %d\n", c0, c1);
    return 0;
}
