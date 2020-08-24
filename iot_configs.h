// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOT_CONFIGS_H
#define IOT_CONFIGS_H

/**
 * Telegraph Setup
 */
#define LEDPin 16;
#define telegraphPin 5;

/**
 * WiFi setup
 */
#define IOT_CONFIG_WIFI_SSID            "<Enter your Wi-Fi SSID>"
#define IOT_CONFIG_WIFI_PASSWORD        "<Enter your Wi-Fi Password"

/**
 * 
 * IoT Hub Setup
 * 
 */
#define MESSAGE_MAX_LEN 256
#define DEVICE_ID  "<Enter your IoT Hub Device ID>"

/**
 * IoT Hub Device Connection String setup
 * Find your Device Connection String by going to your Azure portal, creating (or navigating to) an IoT Hub, 
 * navigating to IoT Devices tab on the left, and creating (or selecting an existing) IoT Device. 
 * Then click on the named Device ID, and you will have able to copy the Primary or Secondary Device Connection String to this sample.
 */
#define DEVICE_CONNECTION_STRING    "<Paste in your IoT Hub Device Primary Connection String>"

#endif /* IOT_CONFIGS_H */
