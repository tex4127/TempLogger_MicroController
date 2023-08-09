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
  thermo.begin();
  thermo.setThermocoupleType(MAX31856_TCTYPE_J);
  data.ambientTemp = 30.0;
  printHeader();
}

void loop() 
{
  startTime = millis();
  while (millis() - startTime < CycleTime)
  {
    //measure the ambient temp
    data.ambientTemp = getAmbientTemp();
    //measure the probe voltage and temp
    data.TCoupleCJTempC = thermo.readCJTemperature();
    data.TCoupleTempC = thermo.readThermocoupleTemperature();
    //rinse and repeat (we can add averaging here if we want to)
  }
  //print the data to the serial port
  printDataStruct(&data);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  //Serial.println(millis());
}
