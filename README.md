# ClaudeM5STACK

ESP-IDF firmware for the M5Stack CoreS3 (ESP32-S3, 16MB flash, 8MB PSRAM).

Uses Espressif's [`m5stack_core_s3` BSP](https://components.espressif.com/components/espressif/m5stack_core_s3)
for display, touch, power (AXP2101) and IO expander setup, with LVGL 9 for the UI.

## Build

GitHub Actions builds on every push. Download the `firmware-cores3` artifact from the workflow run.

Local build (ESP-IDF 5.4 or newer):

```bash
idf.py set-target esp32s3
idf.py build
```

## Flash

From a local build:

```bash
idf.py -p /dev/ttyACM0 flash monitor
```

From the CI artifact (merged image, write at offset 0):

```bash
esptool.py --chip esp32s3 -p /dev/ttyACM0 write_flash 0x0 firmware-merged.bin
```

If the port doesn't appear, hold the reset button for ~3 seconds until the green LED lights to enter download mode.
