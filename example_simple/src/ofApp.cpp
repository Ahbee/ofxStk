#include "ofApp.h"

const float NoteC = 65.41;
const float NoteD = 73.42;
const float NoteE = 82.41;
const float NoteF = 87.31;
const float NoteG = 98.0;
const float NoteA = 110.0;
const float NoteB = 123.47;
const float NoteC2 = 130.81;
const float NoteD2 = 146.83;

const int op4FeedbackCC = 2;
const int op3GainCC = 4;
const int LFOSpeedCC = 11;
const int LFODepthCC = 1;


//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("Synth Settings");
    gui.add(op4Feedback.setup("op4Feedback",60,0,127));
    gui.add(op3Gain.setup("op3Gain",60,0,127));
    gui.add(lfoSpeed.setup("LfoSpeed",0,0,127));
    gui.add(lfoDepth.setup("LfoDepth",0,0,127));
    
    intructions.loadFont("verdana.ttf", 20);
    
    stk::Stk::setSampleRate(44100.0);
    ofSoundStreamSetup(2, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    synth.controlChange(op4FeedbackCC, op4Feedback);
    synth.controlChange(op3GainCC, op3Gain);
    synth.controlChange(LFOSpeedCC, lfoSpeed);
    synth.controlChange(LFODepthCC, lfoDepth);
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    intructions.drawString("Press keys a,s,d,f,g,h,j,k,l to play synth", 20,150);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    float amplitude = .5;
    switch (key) {
        case 'a':
            synth.noteOn(NoteC, amplitude);
            aDown = true;
            break;
        case 's':
            synth.noteOn(NoteD, amplitude);
            sDown = true;
            break;
        case 'd':
            synth.noteOn(NoteE, amplitude);
            dDown = true;
            break;
        case 'f':
            synth.noteOn(NoteF, amplitude);
            fDown = true;
            break;
        case 'g':
            synth.noteOn(NoteG, amplitude);
            gDown = true;
            break;
        case 'h':
            synth.noteOn(NoteA, amplitude);
            hDown = true;
            break;
        case 'j':
            synth.noteOn(NoteB, amplitude);
            jDown = true;
            break;
        case 'k':
            synth.noteOn(NoteC2, amplitude);
            kDown = true;
            break;
        case 'l':
            synth.noteOn(NoteD2, amplitude);
            lDown = true;
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'a':
            aDown = false;
            break;
        case 's':
            sDown = false;
            break;
        case 'd':
            dDown = false;
            break;
        case 'f':
            fDown = false;
            break;
        case 'g':
            gDown = false;
            break;
        case 'h':
            hDown = false;
            break;
        case 'j':
            jDown = false;
            break;
        case 'k':
            kDown = false;
            break;
        case 'l':
            lDown = false;
        default:
            break;
    }
    if (noNotesDown()) {
        synth.noteOff(.5);
    }

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

//--------------------------------------------------------------

void ofApp::audioOut(float *output, int bufferSize, int nChannnels){
    stk::StkFrames synthFrames(bufferSize,1);
    synth.tick(synthFrames);
    for (int i = 0; i < bufferSize; i++) {
        output[2*i] = synthFrames(i,0);
        output[2*i+1] =  synthFrames(i,0);
    }
}

bool ofApp::noNotesDown(){
    if (!(aDown || sDown || dDown || fDown || gDown || hDown || jDown || kDown || lDown)) {
        return true;
    }else{
        return false;
    }
}

