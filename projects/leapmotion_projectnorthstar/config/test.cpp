#include <tps61194.h>
#include <stdio.h>

int main(){
    // Dummy pins for pwm, vsync, backlight enable
    TPS61194_ driver(5, 6, 7);
    driver.setup(TPS61194_::vsyncModeSetup::vsyncModeAstableTriggered, 60, 10, 5);
    driver.powerOn();
    driver.brightness(128);
    driver.lightOn();
    driver.lightOff();
    driver.powerOff();
    printf("TPS61194 stub run completed.\n");
    return 0;
}
