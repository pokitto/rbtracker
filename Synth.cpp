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


PaStream *paStream;
PaError paErr;
uint8_t fakeOCR2B;


OSC osc1,osc2;
Instrument patch;

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
mixFunction Marr [] = {mix1, mix2, mix3, updateEnvelopes};

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
            fakeISR(); /** create next sample **/
            *out++ = fakeOCR2B;
            }
    return paContinue; /** THIS IS VERY IMPORTANT !!!! **/
}

void emptyOscillators()
{
    osc1.on = false; osc1.wave = 0; osc1.echo = 0; osc1.count = 0; osc1.cinc =0;
    osc1.attack = 0; osc1.loop = 0; osc1.adsrphase = 0; osc1.adsr = 0; osc1.decay = 0;
    osc1.pitchbend = 0; osc1.bendrate = 0; osc1.maxbend = 0; osc1.sustain = 0; osc1.release = 0;

    osc2.on = false; osc2.wave = 0; osc2.echo = 0; osc2.count = 0; osc2.cinc =0;
    osc2.attack = 0; osc2.loop = 0; osc2.adsrphase = 0; osc2.adsr = 0; osc2.decay = 0;
    osc2.pitchbend = 0; osc2.bendrate = 0; osc2.maxbend = 0; osc2.sustain = 0; osc2.release = 0;
}


void initSound() {

    emptyOscillators();

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
 if (o->count & 0x8000) o->output = 0xFFFF;
 else  o->output = 0;
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
  o->output = random(0,(o->count - 0x7FFF)) << 1 ;
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
    int16_t oldvol = o->vol;
    o->vol += o->attack;
    if (oldvol > o->vol) {
        o->vol = 0xFFFF;
        o->adsrphase = 2;
    }
}

void decayFunc(OSC* o){
    o->vol -= o->decay;
    if (o->vol < o->sustain) {
        o->vol = o->sustain;
        o->adsrphase = 3;
    }
}

void releaseFunc(OSC* o){
    uint16_t oldvol = o->vol;
    o->vol -= o->sustain;
    if (oldvol < o->vol) {
        o->vol = 0;
        if (o->loop) o->adsrphase = 1;
        else o->adsrphase = 0;
    }
}


/** MIXING FUNCTIONS **/

void mix1(){
    // Track 1
    Farr[osc1.wave](&osc1);
    fakeOCR2B = ((osc1.output>>8) * (osc1.vol >>8 )) >> 8 ; // To output, shift back to 8-bit
    tick = 4;
}

void mix2(){
    // Track 2
}

void mix3(){
    // Track 3
}

void updateEnvelopes(){
    //calculate volume envelopes, I do this to save cpu power
    if (voltick) --voltick;
    else {

            if (osc1.pitchbend > osc1.maxbend) osc1.pitchbend += osc1.bendrate;
            voltick = VOLTICK;
    }
}



void fakeISR(){

  osc1.count += osc1.cinc + (osc1.pitchbend >> 8); // counts to 65535 and overflows to zero
  osc2.count += osc2.cinc + (osc2.pitchbend >> 8);; // counts to 65535 and overflows to zero

  Marr[tick](); // call mixing function
  --tick;
}


void setOSC(OSC* o,byte on=1, byte wave=1, byte loop=0, byte echo=0, byte adsr=0,
            uint8_t notenumber=25, uint8_t volume=127,
            uint16_t attack=0, uint16_t decay=0, uint16_t sustain=0, uint16_t release=0,
            int16_t pitchbend=0)
{
  o->on = on;
  o->wave = wave;
  o->loop = loop;
  o->echo = echo;
  o->adsr = adsr;

  o->cinc = cincs[notenumber]; // direct cinc from table, no calculation
  o->vol = volume << 8;//volume;

  if (adsr) {
    o->adsrphase = 1;
    o->adsrvol = 0;
    o->attack = 20; // just a test value
    o->decay = 20;
    o->sustain = 50;
    o->release = 1;
  } else {
    o->adsrphase = 1;
    o->adsrvol = 0;
  }

  if (pitchbend != 0) {
        o->bendrate = -100; // test value
        o->pitchbend = 0;
        o->maxbend = -30000;
  }
}

void output2file() {
    std::ofstream myfile;
    uint16_t j;
    myfile.open ("output.txt");
    patch.count=0;

    /** create sound buffer by using the ISR **/
    for (j=0;j<NUMFRAMES;j++) {
            fakeISR(); /** create next sample **/
            myfile << int(fakeOCR2B) << ",";
            myfile << std::endl;
    }
    myfile.close();
}
