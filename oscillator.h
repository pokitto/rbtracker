#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#define WOFF     0
#define WSQUARE  1
#define WSAW     2
#define WTRI     3
#define WNOISE   4
#define WSAMPLE  5

#define MAXVOL  255
#define DEFAULTPITCH 100
#define DEFAULTLENGTH 65536/2


//#include <Arduino.h>

extern void testOsc();
extern void fakeISR();

typedef uint8_t byte;
typedef uint8_t boolean;

struct ADSR
{
  boolean on;
  uint16_t level;
  int16_t increment;
  uint16_t Apos;
  uint16_t Dpos;
  uint16_t Spos;
  uint16_t Rpos;
  uint8_t Aval;
  uint8_t Dval;
  uint8_t Sval;
  uint8_t Rval;
  int16_t Ainc;
  int16_t Dinc;
  int16_t Sinc;
  int16_t Rinc;
};

struct PITCHENV
{
  boolean on;
  uint16_t level;
  int16_t increment;
  uint16_t P1pos;
  uint16_t P2pos;
  uint8_t P1val;
  uint8_t P2val;
  int16_t P1inc;
  int16_t P2inc;
};

struct OSC {
  byte on;
  byte wave;
  uint16_t pitch;
  uint16_t count;
  int8_t increment;

  int16_t wslope;
  uint16_t wcycle;

  uint16_t vol;
  uint16_t cinc; // how much to add per cycle
  uint16_t output; // output is stored as  16 bit value and shifted before its put in OCR2B

  ADSR adsr;
  int16_t adsrinc;

  PITCHENV pitchenv;

  uint16_t samplepos;
  uint16_t samplelength;
};

#endif
