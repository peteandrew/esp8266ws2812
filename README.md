This project is an adaptation of the esp-httpd project written by Spritetm https://github.com/Spritetm/esphttpd

This project adds WS2812 control based on the WS2812 I2S project by CNLohr https://github.com/cnlohr/esp8266ws2812i2s


export PATH=${PWD}/esp-open-sdk/xtensa-lx106-elf/bin:$PATH
export SDK_BASE=${PWD}/esp-open-sdk/sdk
export ESPTOOL=${PWD}/esptool/esptool.py
export ESPPORT=/dev/ttyUSB0
export ESPBAUD=460800

git submodule init
git submodule update

make USE_OPENSDK=yes
