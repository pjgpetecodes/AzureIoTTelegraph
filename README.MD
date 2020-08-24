# An Azure IoT Hub Connected Telegraph based on an ESP8266.

Part of my talk "A Short History of IoT" at Notts Techfast 27/08/20.

## Instructions

- You will need to fill in the relevant details in the iot_configs.h file to configure the solution
- You will need to copy the platform.local.txt file to (replace with latest version number);
    > %localappdata%\Arduino15\packages\esp8266\hardware\esp8266\2.7.4
- You will need to create an IoT Hub and add a new device. Then copy it's primary connection string to use in iot_configs.h

## References

Original Source based on https://www.instructables.com/id/Morse-Code-Decoder/

Original IoT Code taken from Microsoft Azure IoT Samples for ESP8266