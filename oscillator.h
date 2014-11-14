#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#define WOFF     0
#define WSQUARE  1
#define WSAW     2
#define WTRI     3
#define WNOISE   4
#define WSAMPLE  5

//#include <Arduino.h>

extern void fakeISR();

typedef uint8_t byte;
typedef uint8_t boolean;

struct TRACK {
    byte on;
    uint8_t notenumber[64];
    uint8_t instrument[64];
};


struct OSC {
  byte on;
  byte wave;
  byte loop;
  byte echo;
  byte adsr;

  uint16_t count;

  uint16_t vol;
  uint16_t cinc; // how much to add per cycle
  uint16_t output; // output is stored as  16 bit value and shifted before its put in OCR2B

  uint8_t adsrphase;
  uint16_t adsrvol;
  uint16_t attack; // Attack change
  uint16_t decay; // Attack change
  uint16_t sustain; // Attack change
  uint16_t release; // Attack change

  int16_t pitchbend;   // bends cycle counter (more is higher pitch)
  int16_t maxbend; // maximum bend before stopping
  int16_t bendrate; // how much to bend by every cycle

};

#endif
