///////////////////////////////////////////
///
// This is a simple utility file to help organize and simplify the main code base.
// External dependancies may be defined here.
//
//  Author: Jacob Garner, jgarner@radsource.com
//  Date: 8/9/2023
///
///////////////////////////////////////////

#include <Adafruit_MAX31856.h>

#ifndef __UTIL_HH__
#define __UTIL_HH__

#ifndef HWS_BAUD
#define HWS_BAUD 115200
#endif

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#ifndef ulong
#define ulong unsigned long
#endif

#ifndef OUTBUFFER_SIZE
#define OUTBUFFER_SIZE 200
#endif

#ifndef floatCharSize
#define floatCharSize 8
#endif

#ifndef CycleTime
#define CycleTime 120000 //1 minute (60000) moving to 2 minute(120000), whichs hould be 450 cycles over 15 hours
#endif

#define MISO 14 
#define MOSI 16
#define SS 17
#define SCK 15

Adafruit_MAX31856 thermo = Adafruit_MAX31856(SS, MISO, MOSI, SCK);

typedef struct TempData_t
{
  float ambientTemp;
  float TCoupleCJTempC;
  float TCoupleTempC;
} TempData_t;

int printHeader(void)
{
  Serial.print("Time (millis), Ambient Temp (C), Probe Cold Junction Temp (C), Probe Temp (C) \n");
  return 1;
}

int addArgToArray(char* buf, size_t &pos, char* arg, size_t len, bool addComma = true, size_t buf_len = OUTBUFFER_SIZE)
{
  //ALWAYS CHECK THE BUFFER LENGTHS TO PREVENT OVERFLOWS
  if(len + pos >= buf_len)return 0;
  for(size_t i = 0; i < len; i++)
  {
    buf[pos++] = arg[i]+48;
  }
  if(addComma)buf[pos++] = 0x2C;
  return 1;
}

int addArgToArray(char* buf, size_t &pos, float arg, bool addComma = true)
{
  char arg_c[floatCharSize];
  //parameters: the float, the minimum width, the percision, and where to store the char array
  //dtostrf(arg, 6, 4, arg_c);
  sprintf(arg_c, "%f", arg);
  //Add the float (as a char array) to the outbuffer
  addArgToArray(buf, pos, arg_c, sizeof(arg_c)/sizeof(arg_c[0]), addComma);
  return 1;
}

int printDataStruct(TempData_t* t)
{
  /*
  char outBuffer[OUTBUFFER_SIZE];
  size_t pos = 0;
  addArgToArray(outBuffer, pos, t->ambientTemp);
  addArgToArray(outBuffer, pos, t->TCoupleVolts);
  addArgToArray(outBuffer, pos, t->TCoupleTempC, false); //do not add the last comma
  outBuffer[pos++] = '\n'; //add the new line character so that excel knows to start a new row
  Serial.write(outBuffer, pos);
  */
  Serial.println(String(t->ambientTemp) + "," + String(t->TCoupleCJTempC) + "," + String(t->TCoupleTempC)); 
  return 1;
}

int printDataStruct_f(TempData_t* t)
{
  char outBuffer[OUTBUFFER_SIZE];
  size_t pos = 0;
  addArgToArray(outBuffer, pos, t->ambientTemp);
  addArgToArray(outBuffer, pos, t->TCoupleCJTempC);
  addArgToArray(outBuffer, pos, t->TCoupleTempC, false); //do not add the last comma
  outBuffer[pos++] = '\n'; //add the new line character so that excel knows to start a new row
  Serial.write(outBuffer, pos);
  return 1;
}

float getAmbientTemp()
{
  //pulled from here: 
  //https://theorycircuit.com/arduino-internal-temperature-sensor/
  uint wADC;
  float _temp;
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  _temp = (wADC);

  // The returned temperature is in degrees Celcius.
  return (_temp);
}

/*
float InternalTemp(void)
{

}
*/
#endif