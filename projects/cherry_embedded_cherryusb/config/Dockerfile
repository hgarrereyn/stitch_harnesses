ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static CherryUSB library (device core only)
RUN mkdir -p /fuzz/build /fuzz/install/include/common /fuzz/install/include/core /fuzz/install/lib

# Provide a minimal usb_config.h to satisfy compilation
RUN printf "#ifndef USB_CONFIG_H\n#define USB_CONFIG_H\n\n#include <stdio.h>\n#define CONFIG_USB_PRINTF printf\n#define CONFIG_USB_DBG_LEVEL 0\n#define CONFIG_USB_ALIGN_SIZE 4\n#define CONFIG_USBDEV_MAX_BUS 1\n/* Disable EP0 thread and OSAL usage for minimal build */\n/* #define CONFIG_USBDEV_EP0_THREAD 1 */\n#define CONFIG_USBDEV_REQUEST_BUFFER_LEN 1024\n/* No special section attributes on host */\n#define USB_NOCACHE_RAM_SECTION\n\n#endif\n" > /fuzz/build/usb_config.h && \
    cp /fuzz/build/usb_config.h /fuzz/install/include/usb_config.h

# Create stub implementations for USB device controller API to allow linking
RUN printf "#include <stdint.h>\nint usb_dc_init(uint8_t busid){(void)busid;return 0;}\nint usb_dc_deinit(uint8_t busid){(void)busid;return 0;}\nint usbd_set_address(uint8_t busid, const uint8_t addr){(void)busid;(void)addr;return 0;}\nint usbd_set_remote_wakeup(uint8_t busid){(void)busid;return 0;}\nuint8_t usbd_get_port_speed(uint8_t busid){(void)busid;return 0;}\nint usbd_ep_open(uint8_t busid, const void *ep){(void)busid;(void)ep;return 0;}\nint usbd_ep_close(uint8_t busid, const uint8_t ep){(void)busid;(void)ep;return 0;}\nint usbd_ep_set_stall(uint8_t busid, const uint8_t ep){(void)busid;(void)ep;return 0;}\nint usbd_ep_clear_stall(uint8_t busid, const uint8_t ep){(void)busid;(void)ep;return 0;}\nint usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled){(void)busid;(void)ep;if(stalled)*stalled=0;return 0;}\nint usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t len){(void)busid;(void)ep;(void)data;(void)len;return 0;}\nint usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t len){(void)busid;(void)ep;(void)data;(void)len;return 0;}\n" > /fuzz/build/usb_dc_stub.c

# Compile and archive static library
RUN cd /fuzz/src && \
    stitch_libafl_cc -I/fuzz/build -I/fuzz/src -I/fuzz/src/common -I/fuzz/src/core -c core/usbd_core.c -O2 -o /fuzz/build/usbd_core.o && \
    stitch_libafl_cc -c /fuzz/build/usb_dc_stub.c -O2 -o /fuzz/build/usb_dc_stub.o && \
    ar rcs /fuzz/install/lib/libcherryusb.a /fuzz/build/usbd_core.o /fuzz/build/usb_dc_stub.o && \
    cp -a common/*.h /fuzz/install/include/common/ && \
    cp -a core/*.h /fuzz/install/include/core/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
