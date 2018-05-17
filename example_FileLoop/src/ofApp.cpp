#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();
    panel.add(frequency.setup("BeatFrequency",.25,-1,1));
    panel.add(filterCutoff.setup("filter Cutoff",0.0,0.0,.99));
    panel.add(chorusDepth.setup("chorusDepth",.01,0,.1));
    panel.add(chorusFrequency.setup("chorusFrequency",500,1,500));
    panel.add(reverbRoomSize.setup("reverbRoomSize",.3,0,1));
    panel.add(chorusOn.setup("chorusOn",false));
    panel.add(reverbOn.setup("reverbOn",false));
    chorus.setEffectMix(1.0);
    reverb.setEffectMix(.5);
    
    frequency.addListener(this, &ofApp::frequencyChanged);
    chorusDepth.addListener(this, &ofApp::chorusParametersChanged);
    chorusFrequency.addListener(this, &ofApp::chorusParametersChanged);
    reverbRoomSize.addListener(this, &ofApp::reverbParametersChanged);
    filterCutoff.addListener(this, &ofApp::filterCutoffChanged);
    
    
    chorus.setModDepth(chorusDepth);
    chorus.setModFrequency(chorusFrequency);
    reverb.setRoomSize(reverbRoomSize);
    beat.setFrequency(frequency);
    filter.setZero(filterCutoff);
    
    
    beat.openFile(ofToDataPath("beat.wav",true));
    stk::Stk::setSampleRate(44100.0);
    instructions.load("verdana.ttf", 20);
    
    
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = 512;
    soundStream.setup(settings);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    panel.draw();
    instructions.drawString("Press space bar to start and stop audio.\nUse the slider to control frequency.\nFrequency is measured in file loops per second.\nUse the gui to turn on Chorus and Reverb effects", 10, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        shouldPlayAudio = !shouldPlayAudio;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioOut(ofSoundBuffer& buffer){
    auto& output = buffer.getBuffer();
    auto bufferSize = buffer.getNumFrames();
    if (shouldPlayAudio) {
        stk::StkFrames frames(bufferSize,2);
        beat.tick(frames);
        
        // the beat is a 2 channel file , however most effects only work on on channel
        // so we will just use the left channel. If you want to apply effects on the second channel you need to
        //create two sets of effects one for the left channel and one for the right channel
        stk::StkFrames leftChannel(bufferSize,1);
        // copy the left Channel of 'frames' into `leftChannel`
        frames.getChannel(0, leftChannel, 0);
        
        // applys a filter and writes back into leftChannel
        filter.tick(leftChannel);
        
        if (chorusOn) {
            // chrous takes a mono frame and outputs a stereo frame
            // we will only use the left channel of the chorus output
            stk::StkFrames chorusOut(bufferSize,2);
            chorus.tick(leftChannel, chorusOut);
            chorusOut.getChannel(0, leftChannel, 0);
        }
        if (reverbOn) {
            // reverb also takes a mono frame and outputs a stereo frame
            // we will only use the left channel of the reverb output
            stk::StkFrames reverbOut(bufferSize,2);
            reverb.tick(leftChannel,reverbOut,0,0);
            reverbOut.getChannel(0, leftChannel, 0);
        }
        for (int i = 0; i < bufferSize ; i++) {
            output[2*i] = leftChannel(i,0);
            output[2*i+1] = leftChannel(i,0);
        }
    }
}

void ofApp::chorusParametersChanged(float &value){
    chorus.setModDepth(chorusDepth);
    chorus.setModFrequency(chorusFrequency);
}

void ofApp::reverbParametersChanged(float &value){
    reverb.setRoomSize(value);
}

void ofApp::frequencyChanged(float &value){
    beat.setFrequency(value);
}

void ofApp::filterCutoffChanged(float &value){
    filter.setZero(value);
}


