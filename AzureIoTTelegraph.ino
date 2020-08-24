#include <AzureIoTHub.h>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoJson.h>

#include "iot_configs.h" // You must set your wifi SSID, wifi PWD, and your IoTHub Device Connection String in iot_configs.h
#include "sample_init.h"

#ifdef is_esp_board
  #include "Esp.h"
#endif

#include "AzureIoTProtocol_MQTT.h"
#include "iothubtransportmqtt.h"

int telegraphPressed = false;
int telegraphWasPressed = false;
int pulseOnLength = 0;
int pulseStartTime = 0;
int pulseEndTime = 0;
int pulseOffLength = 0;
String code = "";
String message = "";

/**
 * 
 * Setup the required Inputs and Outputs
 * 
 */
void setupIO()
{
    pinMode(LEDPin, OUTPUT);
    pinMode(telegraphPin, INPUT);
}

/*
 * 
 * The Setup Routine
 * 
 */
void setup() {

    delay(100);     // Settling delay

    setupIO();      // Setup the Inputs and outputs
    setupIoTHub();  // Setup the Azure IoT Hub Connection
}

/*
 * 
 * The Main Loop
 * 
 */
void loop(void)
{
  int telegraphState = digitalRead(telegraphPin);

    if (telegraphState == LOW)
    {
        digitalWrite(LEDPin, HIGH);
        
        if (telegraphPressed == true)
        {
          telegraphPressed = false;
          pulseEndTime = millis();
          //Serial.print("Pulse End: ");
          //Serial.print(pulseEndTime);
            
          pulseOnLength = pulseEndTime - pulseStartTime;

          //
          // Is this a valid Telegraph pulse?
          //
          if (pulseOnLength > 50)
          {
            //Serial.print("Valid Pulse Length");
            //Serial.println();        // carriage return after the last label
            //Serial.print("Pulse Length: ");
            //Serial.print(signalLength);
            //Serial.println();        // carriage return after the last label

            //
            // Dot or Dash?
            //
            if (pulseOnLength > 50 && pulseOnLength < 200)        // Dot
            {
              code += ".";
              //Serial.print(".");
              telegraphWasPressed = true;
              //Serial.println();        // carriage return after the last label
            }
            else if (pulseOnLength >= 200 && pulseOnLength < 500) // Dash
            {
              code += "-";
              //Serial.print("-");
              telegraphWasPressed = true;
              //Serial.println();        // carriage return after the last label
            }
            else                        // Invalid length
            {
              // Do nothing
            }
                        
          }          
        }
        else if (telegraphWasPressed == true)         // Valid Telegraph code received...
        {
          //
          // We can now wait for a space, then decode the code...
          //
          if (millis() - pulseEndTime > 300)
          {
            convertor(code);
            code = "";                            //reset code to blank string
            telegraphWasPressed = false;
          }
          
        }
      }
      else
      {
          digitalWrite(LEDPin, LOW);

          //
          // If the Telegraph wasn't active before, then start the pulse width timer
          //
          if (telegraphPressed == false)
          {
              pulseStartTime = millis();
              telegraphPressed = true;
              //Serial.print("Pulse Start: ");
              //Serial.print(pulseStartTime);
              //Serial.println();        // carriage return after the last label
              
          }
      }
}

/*
 * 
 * Convert Morse Code into Letters
 * 
 */
void convertor(String code) {
  
  /*

  Morse Code Table:
  -----------------

  A   . -           N   - .         0   - - - - -
  B   - . . .       O   - - -       1   . - - - -
  C   - . - .       P   . - - .     2   . . - - -
  D   - . .         Q   - - . -     3   . . . - -
  E   .             R   . - .       4   . . . . -
  F   . . - .       S   . . .       5   . . . . .
  G   - - .         T   -           6   - . . . .
  H   . . . .       U   . . -       7   - - . . .
  I   . .           V   . . . -     8   - - - . .
  J   . - - -       W   . - -       9   - - - - .
  K   - . -         X   - . . -
  L   . - . .       Y   - . - - 
  M   - -           Z   - - . .
  
  Send Message    . - . - . -
  Cancel Message  . . . . . .

  */

  /* Based on Converter code here... https://www.instructables.com/id/Morse-Code-Decoder/  */

  static String letters[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
                              ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",".-.", 
                              "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", 
                              "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", 
                              "E"
                            };
  if (code == ".-.-.-")           // Send the Message to the IoT Hub
  {    
    sendMessage(message);
    message = "";
  }
  else if (code == "......")      // Cancel Message
  {
    Serial.println();
    Serial.println("Cancelled...");
    Serial.println();
    message = "";
  }
  else
  {
    int i = 0;

    while (letters[i] != "E")  // Convert the Morse Code into Letters
    {
      if (letters[i] == code)
      {
        //
        // If we're on letters...
        //
        if (i < 26)
        {
          Serial.print(char('A' + i));  
          message += char('A' + i);
        }
        else
        {
          Serial.print(char('A' + i-43));
          message += char('A' + i-43);
        }

        break;
      }
      i++;
    }
    if (letters[i] == "E")
    {
      Serial.print("Unknown Code:");  //if input code doesn't match any letter, error
      Serial.println(code);
    }
  }
  
}
