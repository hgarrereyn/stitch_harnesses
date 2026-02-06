#include <stdio.h>
#include <string.h>
#include <DsHidMini/Ds3Types.h>

int main() {
    DS3_RAW_INPUT_REPORT rpt; 
    memset(&rpt, 0, sizeof(rpt));
    // Center axes to typical idle center to satisfy idle check thresholds
    rpt.LeftThumbX = 0x80; rpt.LeftThumbY = 0x80;
    rpt.RightThumbX = 0x80; rpt.RightThumbY = 0x80;
    int idle = DS3_RAW_IS_IDLE(&rpt);
    printf("Idle? %s\n", idle ? "yes" : "no");
    return 0;
}
