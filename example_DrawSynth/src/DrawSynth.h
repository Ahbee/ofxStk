#pragma once

#include "ofxStk.h"
#include "ofMain.h"

using namespace stk;

class WaveTable:public stk::Function {
public:
    WaveTable():Function(){
        waveFrames.resize(Stk::sampleRate(),1,0.0);
    }
    // inside tick you are responsible for setting lastFrame_
    StkFloat tick(StkFloat input){
        lastFrame_[0] = waveFrames.interpolate(input);
        return lastFrame_[0];
    }
    void setWaveFrames(const StkFrames &frames){
        waveFrames = frames;
    }
    int getTableSize(){
        return waveFrames.frames();
    }
private:
    StkFrames waveFrames;
};

// when creating a custom instrument you must subclass stk::Instrmnt
class DrawSynth:public stk::Instrmnt {
public:
    
    DrawSynth();
    
    virtual void noteOn(StkFloat frequency, StkFloat amplitude );
    virtual void noteOff(StkFloat amplitude);
    virtual void setFrequency( StkFloat frequency);
    virtual StkFloat tick( unsigned int channel = 0 );
    virtual StkFrames& tick( StkFrames& frames, unsigned int channel = 0 );
    
    void setWaveTable(const StkFrames &newWave);
    void setAttack(float attack){ adsr.setAttackTime(attack);}
    void setDecay(float decay){adsr.setDecayTime(decay);}
    void setSustain(float sustain){adsr.setSustainLevel(sustain);}
    void setRelease(float release){ adsr.setReleaseTime(release);}
    void setGain(float gain){this->gain = gain;}
    
private:
    WaveTable waveTable;
    StkFloat frequency;
    ADSR adsr;
    float gain;
    float index;
};