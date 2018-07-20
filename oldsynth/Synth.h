#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>
#include <stdlib.h>
#include "oscillator.h"
#include "notes.h"
#include "portaudio.h"

#define SAMPLE_RATE   (22050) //(57000)
#define POK_AUD_FREQ SAMPLE_RATE
#define NUMFRAMES 570 //1 ms before refresh was 357
#define ARPSTEPMAX 4 // was 5
#define PATTERNLENGTH 64
#define MAXPATTERNS 10
#define MAXBLOCKS 30 // 10 *3

#define SYNTH_STOPPED 0 // sound is off
#define SYNTH_PLAYBACK 1 // if playback (ie song reading) is on
#define SYNTH_EFFECT 2  // if a simultaneous sound effect is used on channel 3

extern uint8_t playMode;

extern void setPitch(int);
extern void setWave(int);
extern void setVolume(int);
extern void initSound();
extern void terminateSound();
extern void killSound();
extern void startSound();
extern void stopSound();
extern void updatePlayback();
extern void initStreams(uint8_t);
extern void emptyOscillators();
extern void emptyPatches();
extern void emptyBlocks();
extern void emptySong();

extern PaTime streamTime;
extern PaTime getStreamTime();
extern PaTime firstSampleTime;
extern PaTime getFirstSampleTime();


extern void setOSC(OSC* o,byte, byte, byte, byte, byte, uint8_t, uint8_t,
            uint16_t, uint16_t, uint16_t, uint16_t,
            int16_t,int16_t, uint8_t, uint8_t, uint8_t);
extern void output2file();
extern void outputADSR(uint16_t);
extern boolean playing, track1on, track2on, track3on, tableRefresh;
extern uint16_t playerpos;
extern uint16_t samplespertick, notetick;
extern long samplesperpattern;

extern void fakeISR();

extern long readindex, writeindex;
extern uint8_t tick, sequencepos;

extern SONG song;
extern OSC osc1,osc2,osc3;
//extern TRACK track[]; // array of tracks
//extern boolean PWMemulation;
extern OSC patch[];
extern BLOCK block[]; // array of blocks

extern int8_t arptable[][5];

#endif /* SYNTH_H */
