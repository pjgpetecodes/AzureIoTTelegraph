# An Azure IoT Hub Connected Telegraph based on an ESP8266.

Part of my talk "A Short History of IoT" at Notts Techfast 27/08/20.

## Instructions


- Add the following to the Additional Boards URLs;
    > http://arduino.esp8266.com/stable/package_esp8266com_index.json

- Install the ESP8266 board from the Board Manager

- Set your board to any compatible ESP8266. e.g. 
Generic ESP8266

- Set your port to the relevant port for the device. e.g. COM3

- Add the following Microsoft libraries to your Arduino IDE
    - AzureIoTHub
    - AzureIoTProtocol_HTTP
    - AzureIoTProtocol_MQQT
    - AzureIoTUtility
    - ArduinoJSON (by Benoit Blanchon)

- Fill in the relevant details in the iot_configs.h file to configure the solution

- You will need to copy the platform.local.txt file to (replace with latest version number);
    > %localappdata%\Arduino15\packages\esp8266\hardware\esp8266\2.7.4
- Create an IoT Hub and add a new device. Then copy it's primary connection string to use in iot_configs.h

- Due to a bug in the ESP8266 platform, you will to;
    - Open
    >%localappdata%\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266\Arduino.h
    - Comment out the following line (add a // at the start) (currently line 137);
    > #define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))


## References

Original Source based on: https://www.instructables.com/id/Morse-Code-Decoder/

Original IoT Code taken from Microsoft Azure IoT Samples for ESP8266: https://github.com/Azure/azure-iot-arduino