#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#define RBTRACKER_VERSION 0.03f

#define WOFF     0
#define WSQUARE  1
#define WSAW     2
#define WTRI     3
#define WNOISE   4
#define WTNOISE  5
#define WSAMPLE  6

#define OPT_ADSR 1
#define OPT_LOOP 2
#define OPT_ECHO 4
#define OPT_OVERDRIVE 8
#define OPT_NORMALIZE 0x10

#define OVERDRIVE 4

//#include <Arduino.h>

extern void fakeISR();

typedef uint8_t byte;
typedef uint8_t boolean;

struct SONG {
    byte rb_version; // rbtracker version with which the song was created
    uint16_t song_bpm; // song beats per minute
    byte num_patches; // how many different instruments ie patches
    byte num_channels; // how many channels are used by this song (1-3)
    byte num_patterns; // how many different patterns are used
    byte song_end;  // at what position song ends
    int8_t song_loop; // where to loop at end of song. -1 means no loop
    byte block_sequence[3][10]; //the sequence of blocks for each track
    const uint8_t * instrument_stream[3]; //pointers to the instruments in the track streams
    const uint8_t * note_stream[3]; //pointers to the notes in the track streams
};

struct TRACK {
    byte on;
    uint8_t notenumber[640]; // was 64
    uint8_t instrument[640]; // was 64
};

struct BLOCK {
    uint8_t notenumber[64]; // was 64
    uint8_t instrument[64]; // was 64
};

struct OSC {
  byte on;
  byte wave;
  byte loop;
  byte echo;
  byte echodiv;
  byte adsr;
  byte tonic;

  uint32_t count;

  uint16_t vol;
  uint32_t cinc; // how much to add per cycle
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

  uint8_t vibrate;
  uint8_t arpmode;
  uint8_t arpspeed;
  uint8_t arpstep;
  uint8_t overdrive;
  uint8_t kick;

};

#endif
