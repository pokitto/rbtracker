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
boolean playing=false; //external to share between player and synth
boolean track1on = true, track2on = true, track3on = true, tableRefresh = false;

PaStream *paStream;
PaStream *playbackStream;
PaError paErr;
PaTime streamTime;
PaTime firstSampleTime;
PaTime ptnTime;

uint8_t fakeOCR2B, playMode = SYNTH_STOPPED, sequencepos=0;
long writeindex=0, readindex=0;
uint16_t playerpos=0, noiseval, noiseval2;
uint16_t samplespertick=0, notetick; // samplespertick is a calculated value based on song speed. notetick is a counter
long samplesperpattern=0;

int8_t arptable[6][5] = {
{0,0,0,0,0}, // Off
{0,4,7,4,0}, // Major tonic, 3rd, 5th
{0,3,7,3,0}, // Minor tonic, 3rd, 5th
{0,1,0,-1,0}, // vibrato test
{0,12,0,12,0}, // octave test
{0,11,14,17,21}, // funky test
};

SONG song;
OSC osc1,osc2,osc3;
//TRACK track[3];
OSC patch[16];
BLOCK block[30]; //30 blocks maximum

#define VOLTICK 5
#define ARPTICK 150 // was 200
uint8_t tick=3; // loops between 3 channels. Tick 3 is used to calculate volume envelopes
char voltick=0; // i need to make volume changes even slower
uint16_t arptick=0; // i need to make volume changes even slower
int8_t bendtick = 0; // ditto for bend.

void emptyOscillators();

typedef void (*waveFunction)(OSC*);
typedef void (*envFunction)(OSC*);
typedef void (*mixFunction)();

#define NUMWAVES 5
#define NUMENVELOPES 3
#define NUMMIXES 4

void waveoff(OSC* o); void sqwave(OSC* o); void sawwave(OSC* o); void triwave(OSC* o); void noise(OSC* o); void tonenoise(OSC* o); void sample(OSC* o);
void noADSR(OSC* o); void attackFunc(OSC* o); void decayFunc(OSC* o); void releaseFunc(OSC* o);
void mix1(); void mix2(); void mix3(); void updateEnvelopes();

waveFunction Farr []  = {waveoff, sqwave, sawwave, triwave, noise, tonenoise};
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

PaTime getStreamTime() {
    return Pa_GetStreamTime(paStream);
}

PaTime getFirstSampleTime() {
    return firstSampleTime;
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
    firstSampleTime = timeInfo->outputBufferDacTime;

    /** create sound buffer by using the ISR **/

    for (j=0;j<framesPerBuffer;j++) {
        fakeISR(); // create next sample
        if (playing) {
                notetick++;
                updatePlayback();
        }
        *out++ = fakeOCR2B;
    }
    return paContinue; /** THIS IS VERY IMPORTANT !!!! **/
}

void updatePlayback() {
    // samplespertick determines how long the oscillators are active before they are recalculated (i.e. the next tick
    uint8_t i=0;

    if (notetick > samplespertick ) {
            // TRACK 1
            if (track1on) i = *song.instrument_stream[0];
            else i = 0;
            if (i) {
                setOSC(&osc1,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                *song.note_stream[0],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate, patch[i].arpmode, patch[i].overdrive, patch[i].kick );
                }
            // TRACK 2
            if (track2on) i = *song.instrument_stream[1];
            else i = 0;
            if (i) {
                setOSC(&osc2,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                *song.note_stream[1],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate, patch[i].arpmode, patch[i].overdrive, patch[i].kick );
                }
            // TRACK 3
            //if (track[2].on) i = track[2].instrument[playerpos];
            if (track3on) i = *song.instrument_stream[2];
            else i = 0;
            if (i) {
                setOSC(&osc3,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                *song.note_stream[2],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate, patch[i].arpmode, patch[i].overdrive, patch[i].kick );
                }
            playerpos++;
            song.instrument_stream[0]++;
            song.note_stream[0]++;
            song.instrument_stream[1]++;
            song.note_stream[1]++;
            song.instrument_stream[2]++;
            song.note_stream[2]++;
            if (playerpos == PATTERNLENGTH) {
                    // move to next song position
                    sequencepos++;
                    if (sequencepos > song.song_end) {
                        if (song.song_loop == -1) {
                            emptyOscillators();
                            playing = false;
                            sequencepos--;
                        } else {
                            sequencepos = song.song_loop;
                        }
                    }
                    playerpos = 0;
                    initStreams(sequencepos);
                    tableRefresh=true;
            }
            notetick =0;
            }
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
    patch[i].pitchbend = 0; patch[i].bendrate = 0; patch[i].maxbend = 0; patch[i].sustain = 0; patch[i].release = 0, patch[i].overdrive = 0, patch[i].kick = 0;
    }
}

void emptyTracks()
{
    track1on = track2on = track3on = true;
    /*for (int i=0; i<PATTERNLENGTH*MAXPATTERNS; i++) {
        track[0].instrument[i] = 0; track[0].notenumber[i] = 255;
        track[1].instrument[i] = 0; track[1].notenumber[i] = 255;
        track[2].instrument[i] = 0; track[2].notenumber[i] = 255;
    }*/
}

void emptyBlocks()
{
    for (int i=0; i<MAXBLOCKS; i++) {
            for (int j = 0; j < PATTERNLENGTH; j++) {
                    block[i].instrument[j] = 0;
                    block[i].notenumber[j] = 255;
            }
    }
}

void initStreams(uint8_t seqpos)
{
    uint8_t blocknum;
    // retarget pointers for track 1
    blocknum=song.block_sequence[0][seqpos];
    song.instrument_stream[0]=&block[blocknum].instrument[0];
    song.note_stream[0]=&block[blocknum].notenumber[0];
    // retarget pointers for track 2
    blocknum=song.block_sequence[1][seqpos];
    song.instrument_stream[1]=&block[blocknum].instrument[0];
    song.note_stream[1]=&block[blocknum].notenumber[0];
    // retarget pointers for track 3
    blocknum=song.block_sequence[2][seqpos];
    song.instrument_stream[2]=&block[blocknum].instrument[0];
    song.note_stream[2]=&block[blocknum].notenumber[0];
}


void emptySong()
{
    song.num_channels = 3;
    song.num_patches = 1;
    song.song_bpm = 120;
    song.num_patterns = 1;
    song.song_end = 0;
    song.song_loop = 0; // loop back to start
    song.rb_version = RBTRACKER_VERSION;
    for (uint8_t i = 0; i<10; i++) {
        song.block_sequence[0][i]=i*3; // track 1
        song.block_sequence[1][i]=i*3+1; // track 2
        song.block_sequence[2][i]=i*3+2; // track 3
    }
    song.instrument_stream[0] = &block[0].instrument[0];
    song.note_stream[0] = &block[0].notenumber[0];
    song.instrument_stream[1] = &block[1].instrument[0];
    song.note_stream[1] = &block[1].notenumber[0];
    song.instrument_stream[2] = &block[2].instrument[0];
    song.note_stream[2] = &block[2].notenumber[0];
    sequencepos = 0;
}


void initSound() {

    emptySong();
    emptyOscillators();
    //emptyTracks();
    emptyBlocks();
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

    //paErr = Pa_StartStream( paStream );
    //if( paErr != paNoError ) goto error;
    return;

error:
    Pa_Terminate();
    return;

}

void terminateSound() {
    Pa_AbortStream(paStream);
    Pa_CloseStream(paStream);
    Pa_Terminate();
}

void startSound() {
    paErr = Pa_StartStream( paStream );
    if( paErr != paNoError ) goto error;
    return;

error:
    Pa_Terminate();
    return;
}

void stopSound() {
    paErr = Pa_StopStream( paStream );
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
 if (o->count & 0x80000000) o->output = 0;
 else  o->output = 0xFFFF;
}

void sawwave(OSC* o){
 // saw is just twice the count, so it happens 2 times in a cycle.
 o->output = (o->count>>16) << 1; // simple, eh ?
}

void triwave(OSC* o){
    // exploit the fact that above 0x7FFF bit 16 will be set (ie. when on second side of cycle)
    if (o->count & 0x80000000) o->output = ((~o->count)>>16) << 1; // counts down because complement goes other way
    else o->output = (o->count>>16) << 1; // count up on first side of cycle
}

void noise(OSC* o){
  if (o->count > 0x80000000) {
    o->output = noiseval2;
    noiseval = random(0,0xFFFF);
  }
  else  {
    o->output = noiseval;
    noiseval2 = random(0,0xFFFF);
  }
}

void tonenoise(OSC* o){
  // square. If bit 16 set, its 2nd half of cycle and then output. if not, silence.
 if (o->count & 0x80000000) o->output = 0;
 else  o->output = random(0,0xFFFF);
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
    if (o->adsrvol > o->release) o->adsrvol -= o->release;
    else o->adsrvol = 0;
    if (!o->adsrvol) { // we have hit zero volume level
        if (o->loop) {
                if (o->attack) {
                    o->adsrvol = 0;
                } else {
                    o->adsrvol = o->vol;
                }
                if (o->echo) o->echodiv++;
                o->adsrphase = 1;
                return;
        }
        else {
                o->adsrphase = 0;
                o->adsrvol = 0;
                return;
        }
    }
}


/** MIXING FUNCTIONS **/

void mix1(){
    // Track 1
    Farr[osc1.wave](&osc1);
    fakeOCR2B = (((osc1.output>>8) * (osc1.adsrvol >>8 )) >> 8) >> osc1.echodiv; // To output, shift back to 8-bit
    if (osc1.overdrive) fakeOCR2B *= OVERDRIVE;
    if (osc1.kick ) fakeOCR2B >>= 2;

}

void mix2(){
    // Track 2
    Farr[osc2.wave](&osc2);
    fakeOCR2B = (((osc2.output>>8) * (osc2.adsrvol >>8 )) >> 8) >> osc2.echodiv;
    if (osc2.overdrive) fakeOCR2B *= OVERDRIVE;
    if (osc2.kick ) fakeOCR2B >>= 2;
}

void mix3(){
    // Track 3
    Farr[osc3.wave](&osc3);
    fakeOCR2B = (((osc3.output>>8) * (osc3.adsrvol >>8 )) >> 8) >> osc3.echodiv;
    if (osc3.overdrive) fakeOCR2B *= OVERDRIVE;
    if (osc3.kick ) fakeOCR2B >>= 2;
}

void updateEnvelopes(){
    //calculate volume envelopes, I do this to save cpu power
    if (arptick) --arptick;
    else {
            if (osc1.arpmode) {
                osc1.cinc = cincs[osc1.tonic+arptable[osc1.arpmode][osc1.arpstep]];
                osc1.arpstep++;
                if (osc1.arpstep==ARPSTEPMAX) osc1.arpstep = 0;
                arptick = ARPTICK << (3-osc1.arpspeed);
            }
            if (osc2.arpmode) {
                osc2.cinc = cincs[osc2.tonic+arptable[osc2.arpmode][osc2.arpstep]];
                osc2.arpstep++;
                if (osc2.arpstep==ARPSTEPMAX) osc2.arpstep = 0;
                arptick = ARPTICK << (3-osc2.arpspeed);
            }
            if (osc3.arpmode) {
                osc3.cinc = cincs[osc3.tonic+arptable[osc3.arpmode][osc3.arpstep]];
                osc3.arpstep++;
                if (osc3.arpstep==ARPSTEPMAX) osc3.arpstep = 0;
                arptick = ARPTICK << (3-osc3.arpspeed);
            }

    }

    if (voltick) --voltick;
    else {
            bendtick = !bendtick;
            Earr[osc1.adsrphase](&osc1);
            if (bendtick) osc1.pitchbend += osc1.bendrate; //slow bend to every second beat
            if (osc1.bendrate > 0 && osc1.pitchbend > osc1.maxbend) {
                    osc1.pitchbend = osc1.maxbend;
                    osc1.bendrate = 0; // STOP BENDING !
            }
            else if (osc1.bendrate < 0 && osc1.pitchbend < osc1.maxbend) {
                    osc1.pitchbend = osc1.maxbend;
                    osc1.bendrate = 0; // STOP BENDING !
            }

            Earr[osc2.adsrphase](&osc2);
            if (bendtick) osc2.pitchbend += osc2.bendrate;
            if (osc2.bendrate > 0 && osc2.pitchbend > osc2.maxbend) osc2.pitchbend = osc2.maxbend;
            else if (osc2.bendrate < 0 && osc2.pitchbend < osc2.maxbend) osc2.pitchbend = osc2.maxbend;

            Earr[osc3.adsrphase](&osc3);
            if (bendtick) osc3.pitchbend += osc3.bendrate;
            if (osc3.bendrate > 0 && osc3.pitchbend > osc3.maxbend) osc3.pitchbend = osc3.maxbend;
            else if (osc3.bendrate < 0 && osc3.pitchbend < osc3.maxbend) osc3.pitchbend = osc3.maxbend;

            voltick = VOLTICK;
    }
    tick = 4;
}



void fakeISR(){

  osc1.count += osc1.cinc + (osc1.pitchbend >> 4); // counts to 65535 and overflows to zero WAS 8 !
  osc2.count += osc2.cinc + (osc2.pitchbend >> 4); // counts to 65535 and overflows to zero
  osc3.count += osc3.cinc + (osc3.pitchbend >> 4); // counts to 65535 and overflows to zero

  Marr[tick](); // call mixing function
  --tick;
}


void setOSC(OSC* o,byte on=1, byte wave=1, byte loop=0, byte echo=0, byte adsr=0,
            uint8_t notenumber=25, uint8_t volume=127,
            uint16_t attack=0, uint16_t decay=0, uint16_t sustain=0, uint16_t release=0,
            int16_t maxbend=0, int16_t bendrate=0, uint8_t arpmode = 0, uint8_t overdrive=0, uint8_t kick=0)
{
  o->on = on;
  o->overdrive = overdrive;
  o->kick = kick;
  o->wave = wave;
  o->loop = loop;
  o->echo = echo; //echo shifts left 8 steps to zero
  o->echodiv = 0;
  o->adsr = adsr;
  if (arpmode) {
        if (arpmode < 4) {o->arpmode = 1; o->arpspeed = arpmode;}
        else if (arpmode < 7) {o->arpmode = 2; o->arpspeed = arpmode-3;}
        else if (arpmode < 10) {o->arpmode = 3; o->arpspeed = arpmode-6; } // vibrato trial
        else if (arpmode < 13) {o->arpmode = 4; o->arpspeed = arpmode-9; } // octave trial
        else if (arpmode < 16) {o->arpmode = 5; o->arpspeed = arpmode-12; } // funk trial*/
  } else o->arpmode = 0;
  o->arpstep = 0;
  o->count = 0;
  noiseval = random(0,0xFFFF);

  o->cinc = cincs[notenumber]; // direct cinc from table, no calculation
  o->tonic = notenumber; // save tonic for arpeggio use
  if (wave == 2) o->cinc >>= 1; // correct pitch for saw wave
  if (wave == 4) o->cinc <<= 1; // enable higher pitch for pure noise
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

