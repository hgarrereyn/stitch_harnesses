ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Prepare install dirs and minimal TinyUSB config header
RUN set -eux; \
    install -d /fuzz/build /fuzz/install/lib /fuzz/install/include; \
    printf '%s\n' \
      '#ifndef TUSB_CONFIG_FUZZ_H' \
      '#define TUSB_CONFIG_FUZZ_H' \
      '#define CFG_TUSB_MCU OPT_MCU_NONE' \
      '#define CFG_TUSB_OS  OPT_OS_NONE' \
      '#define CFG_TUD_ENABLED 0' \
      '#define CFG_TUH_ENABLED 0' \
      '#define CFG_TUD_ENDPOINT0_SIZE 64' \
      '#endif' \
      > /fuzz/build/tusb_config_fuzz.h; \
    cp /fuzz/build/tusb_config_fuzz.h /fuzz/install/include/

# Build static library and install headers
RUN set -eux; \
    cd /fuzz/build; \
    SRC_ROOT=/fuzz/src/src; \
    NET_ROOT=/fuzz/src/lib/networking; \
    SRC_FILES="$SRC_ROOT/tusb.c $SRC_ROOT/common/tusb_fifo.c $SRC_ROOT/device/usbd.c $SRC_ROOT/device/usbd_control.c $SRC_ROOT/class/audio/audio_device.c $SRC_ROOT/class/cdc/cdc_device.c $SRC_ROOT/class/dfu/dfu_device.c $SRC_ROOT/class/dfu/dfu_rt_device.c $SRC_ROOT/class/hid/hid_device.c $SRC_ROOT/class/midi/midi_device.c $SRC_ROOT/class/msc/msc_device.c $SRC_ROOT/class/mtp/mtp_device.c $SRC_ROOT/class/net/ecm_rndis_device.c $SRC_ROOT/class/net/ncm_device.c $SRC_ROOT/class/usbtmc/usbtmc_device.c $SRC_ROOT/class/vendor/vendor_device.c $SRC_ROOT/class/video/video_device.c $SRC_ROOT/host/usbh.c $SRC_ROOT/host/hub.c $SRC_ROOT/class/cdc/cdc_host.c $SRC_ROOT/class/hid/hid_host.c $SRC_ROOT/class/midi/midi_host.c $SRC_ROOT/class/msc/msc_host.c $SRC_ROOT/class/vendor/vendor_host.c $SRC_ROOT/typec/usbc.c"; \
    for f in $SRC_FILES; do \
      obj=o_$(basename "$f").o; \
      gf_libafl_cc -Os -fPIC -I/fuzz/src/src -I"$SRC_ROOT" -I"$NET_ROOT" -I/fuzz/build \
        -DCFG_TUSB_CONFIG_FILE=\<tusb_config_fuzz.h\> \
        -c "$f" -o "$obj"; \
    done; \
    ar rcs /fuzz/install/lib/libtinyusb.a ./*.o; \
    cp -a /fuzz/src/src/* /fuzz/install/include/; \
    cp -a /fuzz/src/lib/networking /fuzz/install/include/ || true
