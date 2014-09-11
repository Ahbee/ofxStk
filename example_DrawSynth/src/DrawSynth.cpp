#include "DrawSynth.h"

DrawSynth::DrawSynth(){
    index = 0.0;
}

void DrawSynth::noteOn(StkFloat frequency, StkFloat amplitude){
    adsr.keyOn();
    setFrequency(frequency);
    gain = amplitude;
}

void DrawSynth::noteOff(StkFloat amplitude){
    adsr.keyOff();
}

void DrawSynth::setFrequency(StkFloat newFreq){
    frequency = newFreq;
}

// inside tick you are responsible for setting lastFrame_
StkFloat DrawSynth::tick(unsigned int channel){
    int tableSize = waveTable.getTableSize();
    float frqTL = (float)tableSize/Stk::sampleRate();
    float indexIncremet = frqTL * frequency;
    lastFrame_[0] = waveTable.tick(index);
    index+=indexIncremet;
    if (index >= tableSize - 1) {
        index = 0;
    }
    lastFrame_[0]*= adsr.tick();
    lastFrame_[0]*=gain;
    return lastFrame_[0];
}

StkFrames& DrawSynth::tick(StkFrames &frames,unsigned int channel){
    StkFloat *samples = &frames[channel];
    unsigned int hop = frames.channels();
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
        *samples = tick();
    return frames;
}

void DrawSynth::setWaveTable(const stk::StkFrames &frames){
    waveTable.setWaveFrames(frames);
}