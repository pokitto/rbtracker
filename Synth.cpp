#include "Synth.h"
#include "oscillator.h"
#include "utilities.h"
//#include "sounds.h"
#include <math.h>
#include "portaudio.h"
#include "fastdiv.h"
#include <iostream>
#include <fstream>

/** Sound Variables **/


uint8_t data[NUMFRAMES]; //portaudio
boolean playing=false, priming = false; //external to share between player and synth

PaStream *paStream;
PaError paErr;
uint8_t fakeOCR2B;
uint8_t soundbuffer[BUFFERLENGTH];
long writeindex=0, readindex=0;
uint16_t playerpos=0;
long samplespertick=0;
long samplesperpattern=0;


OSC osc1,osc2,osc3;
TRACK track[3];
OSC patch[16];

#define VOLTICK 10
uint8_t tick=3; // loops between 3 channels. Tick 3 is used to calculate volume envelopes
char voltick=VOLTICK; // i need to make volume changes even slower

typedef void (*waveFunction)(OSC*);
typedef void (*envFunction)(OSC*);
typedef void (*mixFunction)();

#define NUMWAVES 5
#define NUMENVELOPES 3
#define NUMMIXES 4

void waveoff(OSC* o); void sqwave(OSC* o); void sawwave(OSC* o); void triwave(OSC* o); void noise(OSC* o); void sample(OSC* o);
void noADSR(OSC* o); void attackFunc(OSC* o); void decayFunc(OSC* o); void releaseFunc(OSC* o);
void mix1(); void mix2(); void mix3(); void updateEnvelopes();

waveFunction Farr []  = {waveoff, sqwave, sawwave, triwave, noise, sample};
envFunction Earr [] = {noADSR, attackFunc, decayFunc, releaseFunc};
mixFunction Marr [] = {updateEnvelopes,mix3,mix2,mix1}; // counts down

// Arduino compatibility

long random(long howbig)
{
  if (howbig == 0) {
    return 0;
  }
    long r;
    r = rand() % howbig;
    return  r;
}

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}


static int paCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    uint8_t *data = (uint8_t*)userData;
    uint8_t *out = (uint8_t*)outputBuffer;
    unsigned long j =0;
    (void) inputBuffer; /* Prevent unused variable warning. */

    /** create sound buffer by using the ISR **/

    for (j=0;j<framesPerBuffer;j++) {
            if (playing) {
                    *out++ = soundbuffer[readindex]; // buffered output because of wxwidgets timing problems
                    readindex++;
                    if (readindex % samplespertick == 0) playerpos++;
                    if (playerpos == 64) playerpos = 0;
                    if (readindex == samplesperpattern) {
                        readindex=0;
                        out = &soundbuffer[0];
                    }
            } else if (!priming) {
                    fakeISR(); /** create next sample **/
                    *out++ = fakeOCR2B;
            } else playerpos =0;
            }

    return paContinue; /** THIS IS VERY IMPORTANT !!!! **/
}

void emptyOscillators()
{
    osc1.on = false; osc1.wave = 0; osc1.echo = 0; osc1.count = 0; osc1.cinc =0;
    osc1.attack = 0; osc1.loop = 0; osc1.adsrphase = 1; osc1.adsr = 1; osc1.decay = 100;
    osc1.pitchbend = 0; osc1.bendrate = 0; osc1.maxbend = 0; osc1.sustain = 0; osc1.release = 0;

    osc2.on = false; osc2.wave = 0; osc2.echo = 0; osc2.count = 0; osc2.cinc =0;
    osc2.attack = 0; osc2.loop = 0; osc2.adsrphase = 1; osc2.adsr = 1; osc2.decay = 100;
    osc2.pitchbend = 0; osc2.bendrate = 0; osc2.maxbend = 0; osc2.sustain = 0; osc2.release = 0;

    osc3.on = false; osc3.wave = 0; osc3.echo = 0; osc3.count = 0; osc3.cinc =0;
    osc3.attack = 0; osc3.loop = 0; osc3.adsrphase = 1; osc3.adsr = 1; osc3.decay = 100;
    osc3.pitchbend = 0; osc3.bendrate = 0; osc3.maxbend = 0; osc3.sustain = 0; osc3.release = 0;
}

void emptyPatches()
{
    for (int i=0; i<16; i++) {
    patch[i].vol = 127;
    patch[i].on = true; patch[i].wave = 1; patch[i].echo = 0; patch[i].count = 0; patch[i].cinc =0;
    patch[i].attack = 0; patch[i].loop = 0; patch[i].adsrphase = 0; patch[i].adsr = 0; patch[i].decay = 20;
    patch[i].pitchbend = 0; patch[i].bendrate = 0; patch[i].maxbend = 0; patch[i].sustain = 0; patch[i].release = 0;
    }
}

void emptyTracks()
{
    track[0].on = track[1].on = track[2].on = true;
    for (int i=0; i<64; i++) {
        track[0].instrument[i] = 0; track[0].notenumber[i] = 255;
        track[1].instrument[i] = 0; track[1].notenumber[i] = 255;
        track[2].instrument[i] = 0; track[2].notenumber[i] = 255;
    }
}


void initSound() {

    emptyOscillators();
    emptyTracks();
    emptyPatches();

    paErr = Pa_Initialize();
    if( paErr != paNoError ) goto error;

    paErr = Pa_OpenDefaultStream( &paStream,
                                0,          /* no input channels */
                                1,          /* mono output */
                                paUInt8,    /* 8 bit output */
                                SAMPLE_RATE,
                                NUMFRAMES,  /* frames per buffer was 256 */
                                paCallback,
                                &data );
    if( paErr != paNoError ) goto error;

    paErr = Pa_StartStream( paStream );
    if( paErr != paNoError ) goto error;
    return;

error:
    Pa_Terminate();
    return;

}

void killSound()
{
     paErr = Pa_StopStream( paStream );
     if( paErr != paNoError ) goto error;
     paErr = Pa_CloseStream( paStream );
     if( paErr != paNoError ) goto error;

error:
    Pa_Terminate();
    return;
}


/** SOUND FUNCTIONS **/


void waveoff(OSC* o){
  o->output = 0;
}

void sqwave(OSC* o){
// square. If bit 16 set, its 2nd half of cycle and then output. if not, silence.
 if (o->count & 0x8000) o->output = 0;
 else  o->output = 0xFFFF;
}

void sawwave(OSC* o){
 // saw is just twice the count, so it happens 2 times in a cycle.
 o->output = o->count << 1; // simple, eh ?
}

void triwave(OSC* o){
    // exploit the fact that above 0x7FFF bit 16 will be set (ie. when on second side of cycle)
    if (o->count & 0x8000) o->output = (~o->count) << 1; // counts down because complement goes other way
    else o->output = o->count << 1; // count up on first side of cycle
}

void noise(OSC* o){
  if (o->count & 0x8000) o->output = 0;
  else  o->output = random(0,0xFFFF);
  //o->output = random(0,(o->count - 0x7FFF)) << 1 ;
  // an even value between 0 and 0xFFFF will be generated ONLY when count > 0x8000 (ie half the loop)
}

void sample(OSC* o) {

    /*if (o->samplepos > o->samplelength ) o->samplepos = 0;

    if (o->count > o->wcycle) {
        o->count=0;
        if (o->output) o->output = 0;
        //else o->output = o->output=pgm_read_byte((uint32_t)(sfxBike) + o->inccount);
    }*/
}

/** ENVELOPE FUNCTIONS **/

void noADSR(OSC* o){
}

void attackFunc(OSC* o){
    if (o->adsrvol >= o->vol) {
        if (o->decay) {
            o->adsrvol = o->vol;
            o->adsrphase = 2;
        } else {
            o->adsrvol = o->sustain;
            o->adsrphase = 3;
        }
        return;
    }
    o->adsrvol += o->attack;
}

void decayFunc(OSC* o){
    if (o->adsrvol >= o->sustain + o->decay) {
        o->adsrvol -= o->decay;
        return;
    } else {
        o->adsrvol = o->sustain;
        o->adsrphase = 3;
    }
}

void releaseFunc(OSC* o){
    if (o->adsrvol >= o->sustain) {
        if (o->loop) {
                if (o->attack) {
                    o->adsrvol = 0;
                } else {
                    o->adsrvol = o->vol;
                }
                o->adsrphase = 1;
                return;
        }
        else {
                o->adsrphase = 0;
                o->adsrvol = 0;
                return;
        }
    }
    o->adsrvol -= o->release;
}


/** MIXING FUNCTIONS **/

void mix1(){
    // Track 1
    Farr[osc1.wave](&osc1);
    if (!playing && !priming) fakeOCR2B = ((osc1.output>>8) * (osc1.adsrvol >>8 )) >> 8 ; // To output, shift back to 8-bit
    else if (priming) soundbuffer[writeindex] = ((osc1.output>>8) * (osc1.adsrvol >>8 )) >> 8;
}

void mix2(){
    // Track 2
    Farr[osc2.wave](&osc2);
    if (!playing && !priming) fakeOCR2B = ((osc2.output>>8) * (osc2.adsrvol >>8 )) >> 8 ; // To output, shift back to 8-bit
    else if (priming) soundbuffer[writeindex] = ((osc2.output>>8) * (osc2.adsrvol >>8 )) >> 8;
}

void mix3(){
    // Track 3
     Farr[osc3.wave](&osc3);
    if (!playing && !priming) fakeOCR2B = ((osc3.output>>8) * (osc3.adsrvol >>8 )) >> 8 ; // To output, shift back to 8-bit
    else if (priming) soundbuffer[writeindex] = ((osc3.output>>8) * (osc3.adsrvol >>8 )) >> 8;
}

void updateEnvelopes(){
    //calculate volume envelopes, I do this to save cpu power
    if (voltick) --voltick;
    else {
            Earr[osc1.adsrphase](&osc1);
            osc1.pitchbend += osc1.bendrate;
            if (osc1.bendrate > 0 && osc1.pitchbend > osc1.maxbend) osc1.pitchbend = osc1.maxbend;
            else if (osc1.bendrate < 0 && osc1.pitchbend < osc1.maxbend) osc1.pitchbend = osc1.maxbend;

            Earr[osc2.adsrphase](&osc2);
            osc2.pitchbend += osc2.bendrate;
            if (osc2.bendrate > 0 && osc2.pitchbend > osc2.maxbend) osc2.pitchbend = osc2.maxbend;
            else if (osc2.bendrate < 0 && osc2.pitchbend < osc2.maxbend) osc2.pitchbend = osc2.maxbend;

            Earr[osc3.adsrphase](&osc3);
            osc3.pitchbend += osc3.bendrate;
            if (osc3.bendrate > 0 && osc3.pitchbend > osc3.maxbend) osc3.pitchbend = osc3.maxbend;
            else if (osc3.bendrate < 0 && osc3.pitchbend < osc3.maxbend) osc3.pitchbend = osc3.maxbend;

            voltick = VOLTICK;
    }
    //if (priming || playing) writeindex --;
    tick = 4;
}



void fakeISR(){

  osc1.count += osc1.cinc + (osc1.pitchbend >> 8); // counts to 65535 and overflows to zero
  osc2.count += osc2.cinc + (osc2.pitchbend >> 8); // counts to 65535 and overflows to zero
  osc3.count += osc3.cinc + (osc3.pitchbend >> 8); // counts to 65535 and overflows to zero

  Marr[tick](); // call mixing function
  --tick;
}


void setOSC(OSC* o,byte on=1, byte wave=1, byte loop=0, byte echo=0, byte adsr=0,
            uint8_t notenumber=25, uint8_t volume=127,
            uint16_t attack=0, uint16_t decay=0, uint16_t sustain=0, uint16_t release=0,
            int16_t maxbend=0, int16_t bendrate=0)
{
  o->on = on;
  o->wave = wave;
  o->loop = loop;
  o->echo = echo;
  o->adsr = adsr;
  o->count = 0;

  o->cinc = cincs[notenumber]; // direct cinc from table, no calculation
  o->vol = volume << 8;//volume;

  if (adsr) {
    o->attack = attack;
    o->decay = decay;
    o->sustain = sustain;
    o->release = release;
    o->adsrphase = 1;
    if (!o->attack) o->adsrvol = o->vol; // start directly, no attack ramp
    else o->adsrvol = 0;
  } else {
    o->attack = 0;
    o->decay = 0;
    o->sustain = 0;
    o->release = 0;
    o->adsrphase = 0;
    o->adsrvol = o->vol; // will stay same all the time
  }

  if (bendrate != 0) {
        o->bendrate = bendrate; // test value
        o->pitchbend = 0;
        o->maxbend = maxbend;
  }
}

void output2file() {
    std::ofstream myfile;
    uint16_t j;
    myfile.open ("output.txt");

    /** create sound buffer by using the ISR **/
    for (j=0;j<NUMFRAMES;j++) {
            fakeISR(); /** create next sample **/
            myfile << int(fakeOCR2B) << ",";
            myfile << std::endl;
    }
    myfile.close();
}

