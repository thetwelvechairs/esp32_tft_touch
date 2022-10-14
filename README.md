````
grep -rl adafruit_feather_esp32_v2 . | xargs sed -i '' 's/eadafruit_feather_esp32_v2/esp32-s3-devkitc-1/g'

platformio -c clion init --ide clion

platformio -c clion run --target upload -e esp32-s3-devkitc-1
````

Hardware
* Adafruit ESP32-S3 TFT Feather

Required drivers

* MacOS http://www.wch-ic.com/downloads/CH34XSER_MAC_ZIP.html
* Windows http://www.wch-ic.com/downloads/CH341SER_ZIP.html

### PlatformIO Dependencies

* lovyan03/LovyanGFX@^0.4.18

### Custom configs