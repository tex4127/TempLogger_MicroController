///////////////////////////////////////////
///
// This source code is for using the Arduino Micro (and other arduino AVR architectures)
//  to monitor and report (via Serial) the ambient temperature and the temperatrue of a probe.
//  This is a sample file upon which other version might be built (i.e. SD Card logging or with a Teensy).
//
//
//  Author: Jacob Garner, jgarner@radsource.com
//  Date: 8/9/2023
///
///////////////////////////////////////////


#include"util.h"

TempData_t data;
ulong startTime;

void setup() 
{
  //Start the serial coms
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //for testing, lets initialize our data
  data.ambientTemp = 30.0;
  data.TCoupleVolts = 120.2;
  data.TCoupleTempC = -20.1;
  printHeader();
}

void loop() 
{
  startTime = millis();
  while (millis()- startTime < CycleTime)
  {
    //measure the ambient temp
    //measure the probe voltage and temp
    //rinse and repeat (we can add averaging here if we want to)
  }
  //print the data to the serial port
  printDataStruct(&data);
  //Serial.println(millis());
}
