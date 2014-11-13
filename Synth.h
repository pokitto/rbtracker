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
#define NUMFRAMES 570/2 //100 ms before refresh
#define PWMLEVELS 32


extern void setPitch(int);
extern void setWave(int);
extern void setVolume(int);
extern void initSound();
extern void killSound();

extern void setOSC(OSC* o,byte, byte, byte, byte, byte, uint8_t, uint8_t,
            uint16_t, uint16_t, uint16_t, uint16_t,
            int16_t);
extern void output2file();
extern void outputADSR(uint16_t);

extern OSC osc1,osc2;
extern boolean PWMemulation;


class Instrument {
public:

    /*Instrument(uint8_t o1=WOFF, uint8_t o2=WOFF,
               uint8_t o1vol=MAXVOL, uint8_t o2vol=MAXVOL,
               uint8_t o1pitch=DEFAULTPITCH, uint8_t o2pitch=DEFAULTPITCH,
               uint8_t mm=ADDMIX, uint16_t vol=MAXVOL*256,
               uint16_t pitch=DEFAULTPITCH, uint16_t instrlength=DEFAULTLENGTH,
               uint8_t arpy = false, uint8_t loopy=true
               );*/

    OSC osc1,osc2;
    uint8_t playing;
    uint8_t mixmode;
    uint16_t mainvol;
    uint16_t mainpitch;
    uint16_t count;
    uint16_t length;
    uint8_t arp;
    uint8_t loop;

	void play();
	void stop();
    void mute(uint8_t);

	void setVolume(uint8_t, uint16_t);
	void setNote(uint8_t);
	void setPitch(uint8_t, uint16_t);
    void setWaveform(uint8_t,uint8_t);
    void setMixing(uint8_t);
    void setAttack(uint8_t, uint16_t, uint16_t);
    void setDecay(uint8_t, uint16_t, uint16_t);
    void setSustain(uint8_t, uint16_t, uint16_t);
    void setRelease(uint8_t, uint16_t, uint16_t);
    void setPitchStart(uint8_t, uint16_t, uint16_t);
    void setPitchMiddle(uint8_t, uint16_t, uint16_t);
    void setPitchEnd(uint8_t, uint16_t, uint16_t);
    void adsrOn(uint8_t);
    void pitchOn(uint8_t);
    void arpOn(uint8_t);
    void loopOn(uint8_t);

private:


};

extern Instrument patch;

#endif /* SYNTH_H */
