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

uint8_t snddatanext=1; // which array sound data comes from next
uint8_t volume=255; //portaudio
PaStream *paStream;
PaError paErr;
uint8_t fakeOCR2B, fakeCount=0;
uint16_t skipstep = 0;
boolean PWMemulation = true;
uint8_t isLoop = true;


int pitch = 440, pitch2 = 100;
long count = 0;
long halfcycle = 0;
long sercheck=0;
boolean sertoggle = false;
int osc2inc = 10;
int pitchbend = 16;

OSC osc1,osc2;
Instrument patch;
OSC* oscptr;
boolean osc12Lock = false;
char tick=0;


typedef void (*waveFunction)(OSC*);

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

void stopSound() {
    patch.playing = false;
    patch.count=0;
}


void initSound() {

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

void playSound(uint8_t loop, uint16_t length) {

    patch.loop = loop;
    patch.length = length;
    patch.playing = true;
    patch.count = 0;
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

    if (o->samplepos > o->samplelength ) o->samplepos = 0;

    if (o->count > o->wcycle) {
        o->count=0;
        if (o->output) o->output = 0;
        //else o->output = o->output=pgm_read_byte((uint32_t)(sfxBike) + o->inccount);
    }
}

#define NUMWAVES 5
waveFunction Farr []  = {waveoff, sqwave, sawwave, triwave, noise, sample};

void fakeISR(){

  osc1.count += osc1.cinc; // counts to 65535 and overflows to zero
  osc2.count++;

  //if (tick==7) {
    Farr[osc1.wave](&osc1);
    Farr[osc2.wave](&osc2);

    fakeOCR2B = osc1.output>>8; // To output, shift back to 8-bit
    tick = 0;
  //} else tick++;
}

void setOSC(OSC* o,byte on, byte wave,uint8_t notenumber, byte volume){

  o->on = on;
  o->wave = wave;
  o->pitch = pitch;

  //o->wcycle = fastdiv(SAMPLE_RATE/2,pitch); // how many calls to ISR to complete a wave cycle
  o->cinc = cincs[notenumber]; // direct cinc from table, no calculation
  o->vol = volume << 8;//volume;

  switch (wave) {
    case WSAW:
    o->wslope = fastdiv(o->vol, o->wcycle); // rate of increase for wave as 16 bit value
    o->increment = 1;
    break;
    case WTRI:
    o->wslope = fastdiv(o->vol, (o->wcycle)); // rate of increase for wave as 16 bit value
    break;
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

void testOsc(){

  setOSC(&osc1,true,WOFF,100,127);
  setOSC(&osc2,true,WSAW,100,240);

}
