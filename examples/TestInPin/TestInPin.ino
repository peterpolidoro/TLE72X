#include "Arduino.h"
#include "SPI.h"
#include "Streaming.h"
#include "TLE72X.h"

const int BAUDRATE = 9600;
const int LOOP_DELAY = 1000;
const int CS_PIN = 49;
const int IN_PIN = 48;
const int IC_COUNT = 4;
// IC_COUNT is the number of power switch IC chips connected in a
// daisy chain on the pcb. There are 8 power switch channels per IC.

// Setting SPI_RESET to true causes the SPI parameters to be reset
// every time before a command is issued over SPI. It could cause
// slight delays and should only be used when you are also
// communicating with other SPI devices with different SPI parameters
const bool SPI_RESET = false;

// Instantiate TLE72X
TLE72X power_switch = TLE72X(CS_PIN);

int channel_count;
uint32_t channels;
uint32_t bit;

void setup()
{
  // Setup serial communications
  Serial.begin(BAUDRATE);

  power_switch.setup(IC_COUNT,SPI_RESET);

  channel_count = power_switch.getChannelCount();

  pinMode(IN_PIN,OUTPUT);
  digitalWrite(IN_PIN,LOW);

  for (int channel=0; channel<channel_count; ++channel)
  {
    if ((channel % 1) == 0)
    {
      power_switch.setChannelOn(channel);
    }
    if ((channel % 2) == 0)
    {
      power_switch.setChannelMapFalse(channel);
    }
  }

}

void loop()
{
  digitalWrite(IN_PIN,LOW);
  Serial << "IN_PIN LOW " << endl;
  delay(LOOP_DELAY);
  digitalWrite(IN_PIN,HIGH);
  Serial << "IN_PIN HIGH " << endl;
  delay(2*LOOP_DELAY);
}