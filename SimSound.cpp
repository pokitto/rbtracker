/**************************************************************************/
/*!
    @file     SimSound.cpp
    @author   Jonne Valola

    @section  LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Jonne Valola
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "SimSound.h"
#include <SDL2/SDL.h>
#include "Synth.h"
#include <stdint.h>

uint16_t soundbyte;

#ifdef SOUNDCAPTURE
FILE* soundfile;
uint8_t soundfilebuffer[2][SFBUFSIZE];
uint8_t activesfbuf=0, writesfbuf=0; uint16_t sfbufindex=0;
#endif // SOUNDCAPTURE

/** Internal to this compilation unit */
SDL_AudioSpec wanted, got;
SDL_AudioDeviceID audioDevice;
uint8_t sound_on;
unsigned int aud_position; /* which sample we are up to */
int aud_len; /* how many samples left to play, stops when <= 0 */
float aud_frequency; /* audio frequency in cycles per sample */
float aud_volume; /* audio volume, 0 - ~32000 */

uint8_t streambyte,output,streamon=0;
uint8_t test=false;
float test2=0;

uint8_t soundbuf[SBUFSIZE];
uint16_t soundbufindex=0;

void pokPauseStream() {
    //streamon=0;
}

void pokPlayStream() {
    //streamon=1;
}

void pokSoundIRQ() {
    uint8_t output=0;
    /** DO ADDITIONAL SOUND PROCESSING (NOT STREAM) OF SOUND HERE **/

        /** if song is being played from sd **/
        if (playing) {
                notetick++;
                updatePlayback();
                //updatePlaybackSD(playerpos&7);
        }
        /** oscillators update **/
        osc1.count += osc1.cinc + (osc1.pitchbend);// >> 4); // counts to 65535 and overflows to zero WAS 8 !
        osc2.count += osc2.cinc + (osc2.pitchbend);// >> 4); // counts to 65535 and overflows to zero
        osc3.count += osc3.cinc + (osc3.pitchbend);// >> 4); // counts to 65535 and overflows to zero
        Marr[tick](); // call mixing function
        --tick;

        /** mixing oscillator output **/
        uint16_t op = (uint16_t) ((osc1.output)*(osc1.vol>>8))>>9;// >> 2 osc1.vol Marr;
        op += (uint16_t) ((osc2.output)*(osc2.vol>>8))>>9;// >> 2 osc1.vol Marr;
        op += (uint16_t) ((osc3.output)*(osc3.vol>>8))>>9;// >> 2 osc1.vol Marr;
        output = (uint8_t) op;


    /** SIMULATOR **/

        soundbyte = output;//3; //decrease volume in simulator vs hardware
        soundbuf[soundbufindex++]=soundbyte;
        if (soundbufindex==SBUFSIZE) soundbufindex=0;
}

/** THE FAKE ISR **/

void fakeISR(void){
    pokSoundIRQ();
}

/** The audio callback **/

void simAudioCallback(void* userdata, uint8_t* stream, int len) {
  uint8_t* buf = (uint8_t*)stream;
  unsigned long j =0;

  /** create sound buffer by using the ISR **/
  for (j=0;j<wanted.samples;j++) {

        /** Move outputted sound to output buffer **/
        if (sound_on == false) soundbyte = 0;
        else fakeISR(); /** create sample **/
        *buf++ = soundbyte;
        #if SOUNDCAPTURE > 0
        soundfilebuffer[activesfbuf][sfbufindex++] = soundbyte;
        if (sfbufindex == SFBUFSIZE) {
            activesfbuf = 1-activesfbuf; // toggle other buffer
            sfbufindex =0;
        }
        #endif // SOUNDCAPTURE
    }
  return;
}


int initSDLAudio() {
    #if SOUNDCAPTURE > 0
    soundfile = fopen("c:\\screencap\\soundcapture.raw", "wb");
    #endif // SOUNDCAPTURE

    SDL_InitSubSystem(SDL_INIT_AUDIO);
    SDL_memset(&wanted, 0, sizeof(wanted)); /* or SDL_zero(want) */
    wanted.freq = SAMPLE_RATE;
    wanted.format = AUDIO_U8;
    wanted.channels = 1;
    wanted.samples = NUMFRAMES;
    wanted.callback = simAudioCallback;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wanted, &got, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if (audioDevice == 0) {
        printf("Failed to open audio: %s\n", SDL_GetError());
        return 0;
    } else {
        if (got.format != wanted.format) { // we let this one thing change.
            printf("We didn't get the right audio format.\n");
        return 0;
        }
    }
    aud_len = got.freq * 5; /* 5 seconds */
    aud_position = 0;
    aud_frequency = 1.0 * SAMPLE_RATE / got.freq; /* 1.0 to make it a float */
    aud_volume = 255; /* ~1/5 max volume */

    SDL_PauseAudioDevice(audioDevice, 0); /* play! */
    return 1;
}

void simSoundEnabled(int v) {
    if (v) sound_on=true;
    else sound_on=false;
}


void soundInit() {
    initSDLAudio();
    simSoundEnabled(true);
    pokPauseStream();
}

void pauseAudio(uint8_t v) {
    SDL_PauseAudio(v);
}




uint8_t pokStreamPaused() {
    //return !streamon;
}


#ifndef WIN32

#define SAVECPU  4
uint8_t savecpu=1;

#endif // WIN32
