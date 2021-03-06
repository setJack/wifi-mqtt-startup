#include <mqtt-helper.h>
#include "device-config.h"

String _ledState = "000";

static const uint8_t redPin = D3;
static const uint8_t bluePin = D2;
static const uint8_t greenPin = D1;

void initLEDs()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void changeState(String message)
{
  _ledState = message;
  digitalWrite(redPin, _ledState[0] == '1');
  digitalWrite(greenPin, _ledState[1] == '1');
  digitalWrite(bluePin, _ledState[2] == '1');
  publishState();
}
// ### LEDs ###

void initSerial();

// -- Initialize --

// -- publish mqtt messages
void publishState()
{
  char msg[4];
  Serial.print("State reached: ");
  Serial.println(_ledState);
  msg[0] = _ledState[0];
  msg[1] = _ledState[1];
  msg[2] = _ledState[2];
  msg[3] = '\0';
  publish(PUBLISH,msg);
}
// ### MQTT ###

// ### Serial Monitor ###
void initSerial()
{
  Serial.begin(115200);
}
// ### Serial Monitor ###

// ## PROGRAM ###
void setup()
{
  initSerial();
  initLEDs();
  initWifi();
  initMqtt(&changeState);
}

void loop()
{
  checkWifi();
  subscribe(SUBSCRIBE, ID_MQTT);
}
// ## PROGRAM ###
