#pragma once

#include "ofMain.h"
#include "ofxStk.h"

class BasicSampler: public stk::Instrmnt{
public:
    BasicSampler(){
        sample = new stk::FileWvIn(ofToDataPath("piano.wav",true));
        baseFrequency = 92.4986056779;
        pithShifter = new stk::PitShift();
        pithShifter->setEffectMix(1.0);
        adsr.setAttackTime(10.0/1000.0);
        adsr.setDecayTime(200/1000.0);
        adsr.setSustainLevel(1.0);
        adsr.setReleaseTime(500.0/1000.0);
    }
    
    ~BasicSampler(){
        delete pithShifter;
        delete sample;
    }
    
    void setFrequency(stk::StkFloat frequency ){
        float shiftRatio = frequency/baseFrequency;
        pithShifter->setShift(shiftRatio);
    }
    
    
    void noteOn(stk::StkFloat frequency,stk::StkFloat amplitude ){
        this->setFrequency( frequency );
        this->amplitude = amplitude;
        adsr.keyOn();
        sample->reset();
    }
    
    void noteOff(stk::StkFloat amplitude ){
        adsr.keyOff();
    }
    
    // inside tick you are responsible for setting lastFrame_
    stk::StkFloat tick(unsigned int channel = 0){
        // we are using just the right channel of the sample
        // we do this by passing 1 to 'sample->tick'
        
        lastFrame_[0] = sample->tick(1);
        float input = lastFrame_[0];
        lastFrame_[0] = pithShifter->tick(lastFrame_[0]);
        float output = lastFrame_[0];
        
        lastFrame_[0] *= adsr.tick();
        lastFrame_[0] *= amplitude;
        return lastFrame_[channel];
    }
    
    // fills the specified 'channel' of 'frames'
    stk::StkFrames& tick(stk::StkFrames &frames,unsigned int channel = 0){
        stk::StkFloat *samples = &frames[channel];
        unsigned int hop = frames.channels();
        for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
            *samples = tick();
        return frames;
    }
    
private:
    stk::PitShift *pithShifter;
    float baseFrequency;
    float amplitude;
    stk::FileWvIn *sample;
    stk::ADSR adsr;
    
};
