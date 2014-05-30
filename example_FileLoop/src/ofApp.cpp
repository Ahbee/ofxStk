#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();
    panel.add(frequency.setup("frequency",.25,-1,1));
    beat.openFile(ofToDataPath("beat.wav"));
    stk::Stk::setSampleRate(44100.0);
    ofSoundStreamSetup(2, 0);
    instructions.loadFont("verdana.ttf", 20);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    beat.setFrequency(frequency);
}

//--------------------------------------------------------------
void ofApp::draw(){
    panel.draw();
    instructions.drawString("Press space bar to start and stop audio.\nUse the slider to control frequency.\nFrequency is measured in file loops per second", 10, 100);
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
        for (int i = 0; i < bufferSize ; i++) {
            output[2*i] = frames(i,0);
            output[2*i+1] = frames(i,1);
        }
    }
}



