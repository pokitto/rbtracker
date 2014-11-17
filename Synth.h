#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>
#include <stdlib.h>
#include "oscillator.h"
#include "notes.h"

#define ADDMIX  0
#define AMMIX   1
#define FMMIX   2

#define NUM_SECONDS   (5)
#define SAMPLE_RATE   (57000)
#define NUMFRAMES 570 //1 ms before refresh was 357
#define PWMLEVELS 32
#define BUFFERLENGTH 5700000


extern void setPitch(int);
extern void setWave(int);
extern void setVolume(int);
extern void initSound();
extern void killSound();

extern void setOSC(OSC* o,byte, byte, byte, byte, byte, uint8_t, uint8_t,
            uint16_t, uint16_t, uint16_t, uint16_t,
            int16_t,int16_t);
extern void output2file();
extern void outputADSR(uint16_t);
extern boolean playing, priming;
extern uint16_t playerpos;
extern long samplespertick;
extern long samplesperpattern;

extern void fakeISR();

extern uint8_t soundbuffer[];
extern long readindex, writeindex;
extern uint8_t tick;

extern OSC osc1,osc2,osc3;
extern TRACK track[]; // array of tracks
extern boolean PWMemulation;
extern OSC patch[];

#endif /* SYNTH_H */
