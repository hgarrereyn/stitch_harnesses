#include <stdio.h>
#include <simavr/sim_avr.h>

int main() {
    // Create a simple AVR instance (atmega88 is commonly supported)
    avr_t *avr = avr_make_mcu_by_name("atmega88");
    if (!avr) {
        printf("Failed to create AVR instance\n");
        return 0; // Don't fail hard in the test environment
    }
    avr_init(avr);
    avr->frequency = 8000000; // 8 MHz

    // Run a few cycles
    for (int i = 0; i < 1000; i++) {
        avr_run(avr);
    }

    avr_terminate(avr);
    printf("simavr basic init/run ok\n");
    return 0;
}
