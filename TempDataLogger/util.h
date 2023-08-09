///////////////////////////////////////////
///
// This is a simple utility file to help organize and simplify the main code base.
// External dependancies may be defined here.
//
//  Author: Jacob Garner, jgarner@radsource.com
//  Date: 8/9/2023
///
///////////////////////////////////////////

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
#define CycleTime 1000
#endif

typedef struct TempData_t
{
  float ambientTemp;
  float TCoupleVolts;
  float TCoupleTempC;
} TempData_t;

int printHeader(void)
{
  Serial.print("Time (millis), Ambient Temp (C), Probe Temp (Volts), Probe Temp (C) \n");
  return 1;
}

int addArgToArray(char* buf, size_t &pos, char* arg, size_t len, bool addComma = true, size_t buf_len = OUTBUFFER_SIZE)
{
  //ALWAYS CHECK THE BUFFER LENGTHS TO PREVENT OVERFLOWS
  if(len + pos >= buf_len)return 0;
  for(size_t i = 0; i < len; i++)
  {
    buf[pos++] = arg[i];
  }
  if(addComma)buf[pos++] = 0x2C;
  return 1;
}

int addArgToArray(char* buf, size_t &pos, float arg, bool addComma = true)
{
  char arg_c[floatCharSize];
  //parameters: the float, the minimum width, the percision, and where to store the char array
  dtostrf(arg, 6, 4, arg_c);
  //Add the float (as a char array) to the outbuffer
  addArgToArray(buf, pos, arg_c, sizeof(arg_c)/sizeof(arg_c[0]), addComma);
  return 1;
}

int printDataStruct(TempData_t* t)
{
  char outBuffer[OUTBUFFER_SIZE];
  size_t pos = 0;
  addArgToArray(outBuffer, pos, t->ambientTemp);
  addArgToArray(outBuffer, pos, t->TCoupleVolts);
  addArgToArray(outBuffer, pos, t->TCoupleTempC, false); //do not add the last comma
  outBuffer[pos++] = '\n'; //add the new line character so that excel knows to start a new row
  Serial.write(outBuffer, pos);
  return 1;
}

int printDataStruct_f(TempData_t* t)
{
  char outBuffer[OUTBUFFER_SIZE];
  size_t pos = 0;
  addArgToArray(outBuffer, pos, t->ambientTemp);
  addArgToArray(outBuffer, pos, t->TCoupleVolts);
  addArgToArray(outBuffer, pos, t->TCoupleTempC, false); //do not add the last comma
  outBuffer[pos++] = '\n'; //add the new line character so that excel knows to start a new row
  Serial.write(outBuffer, pos);
  return 1;
}

/*
float InternalTemp(void)
{

}
*/
#endif