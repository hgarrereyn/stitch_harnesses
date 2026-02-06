#include <stdint.h>
#include <stdio.h>
#include "/fuzz/install/include/oepl-proto.h"
#include "/fuzz/install/include/oepl-esp-ap-proto.h"

int main() {
    struct AvailDataReq req = {0};
    req.lastPacketLQI = 200;
    req.lastPacketRSSI = -42;
    req.temperature = 23;
    req.batteryMv = 3000;

    struct AvailDataInfo info = {0};
    info.dataSize = 4096;
    info.dataType = 0x20; // DATATYPE_IMG_RAW_1BPP

    struct espAvailDataReq esp = {0};
    esp.adr = req;

    printf("AvailDataReq: LQI=%u RSSI=%d Temp=%d Batt=%u DataSize=%u\n",
           req.lastPacketLQI, req.lastPacketRSSI, req.temperature, req.batteryMv, info.dataSize);
    printf("esp src[0]=%u, dataType=%u\n", (unsigned)esp.src[0], (unsigned)info.dataType);
    return 0;
}
