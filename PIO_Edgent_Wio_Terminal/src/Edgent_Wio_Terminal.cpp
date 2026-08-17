/******************************************************************************
 * 1. Please update the Wio Terminal WiFi module (RTL8720) firmware:
 *    https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview
 *
 * 2. The LED and button pins are configured in BoardConfig.h
 *    (the SEEED_WIO_TERMINAL section).
 *
 * 3. Fill in TEMPLATE_ID and TEMPLATE_NAME from your Blynk Template below.
 *    Read more: https://bit.ly/BlynkInject
 *
 * 4. Build and upload the firmware, then open the serial monitor:
 *      pio run -t upload
 *      pio device monitor
 *
 * 5. Use the Blynk IoT App to provision your device:
 *    Menu -> Add new device -> Find devices nearby -> Select your device
 *
 *****************************************************************************/

//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"

/* White labeling (use this ONLY if you have a branded Blynk App) */
//#define BLYNK_VENDOR_PREFIX         "Blynk"
//#define BLYNK_DEFAULT_SERVER        "my-dashboard.com"

/* The firmware version (used for OTA updates) */
#define BLYNK_FIRMWARE_VERSION      "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#include <Arduino.h>
#include <BlynkEdgent.h>
#include "Interaction.h"

void setup()
{
  Serial.begin(115200);
  delay(3000);  // Wait for serial monitor (remove if not needed)
  Serial.println();

  // The amount of time (in seconds) to wait for the user to configure the device.
  // If configuration is skipped, the device will enter IDLE mode. Default: 10 min
  BlynkEdgent.setConfigTimeout(10*60);

  // The amount of times the board enters the config mode automatically.
  // NOTE: 0 means unlimited, and is only useful for testing. Default: 10
  BlynkEdgent.setConfigSkipLimit(0);

  // Edgent state indication and button interaction
  interaction.begin();
  BlynkEdgent.onStateChange([](){
    BLYNK_LOG("State: %s", BlynkEdgent.getStateName());
    interaction.updateIndicator();
  });

  // Initialize Blynk.Edgent
  BlynkEdgent.begin();

  // Attach Blynk console to the Serial
  BlynkEdgent.initConsole(BLYNK_PRINT);
}

void loop()
{
  BlynkEdgent.run();
  interaction.run();
  delay(1);
}
