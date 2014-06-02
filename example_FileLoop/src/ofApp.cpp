#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();
    panel.add(frequency.setup("BeatFrequency",.25,-1,1));
    panel.add(chorusDepth.setup("chorusDepth",.01,0,.1));
    panel.add(chorusFrequency.setup("chorusFrequency",500,1,500));
    panel.add(reverbRoomSize.setup("reverbRoomSize",.3,0,1));
    panel.add(chorusOn.setup("chorusOn",false));
    panel.add(reverbOn.setup("reverbOn",false));
    chorus.setEffectMix(1.0);
    reverb.setEffectMix(.5);
    
    beat.openFile(ofToDataPath("beat.wav"));
    stk::Stk::setSampleRate(44100.0);
    ofSoundStreamSetup(2, 0);
    instructions.loadFont("verdana.ttf", 20);
}

//--------------------------------------------------------------
void ofApp::update(){
    beat.setFrequency(frequency);
    chorus.setModDepth(chorusDepth);
    chorus.setModFrequency(chorusFrequency);
    reverb.setRoomSize(reverbRoomSize);
    
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

void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    if (shouldPlayAudio) {
        stk::StkFrames frames(bufferSize,nChannels);
        beat.tick(frames);
        if (chorusOn) {
            chorus.tick(frames);
        }
        if (reverbOn) {
            reverb.tick(frames);
        }
        for (int i = 0; i < bufferSize ; i++) {
            output[2*i] = frames(i,0);
            output[2*i+1] = frames(i,1);
        }
    }
}



