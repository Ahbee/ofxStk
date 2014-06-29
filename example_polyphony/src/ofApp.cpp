#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    stk::Stk::setRawwavePath(ofToDataPath("rawwaves",true));
    
    instructions.loadFont("verdana.ttf", 20);

    for (int i = 0; i < 100 ; i++) {
        stk::Moog *moog = new stk::Moog();
        voicer.addInstrument(moog);
    }
    c.noteNumber = 36;
    e.noteNumber = 38;
    d.noteNumber = 40;
    f.noteNumber = 41;
    g.noteNumber = 43;
    a.noteNumber = 45;
    b.noteNumber = 47;
    c2.noteNumber = 48;
    d2.noteNumber = 50;
    e2.noteNumber = 52;
    
    ofSoundStreamSetup(2, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    instructions.drawString("Press keys a,s,d,f,g,h,j,k,l to play polyphonic synth", 20,150);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // openframeworks calls keyPressed() even when key is heldDown
    // so we have check if key is already held down before calling noteOn
    
    float gain = 50;
    if (key == 'a') {
        if (!aDown) {
            c.voiceTag = voicer.noteOn(c.noteNumber,gain);
            aDown = true;
        }
    }else if (key == 's'){
        if (!sDown) {
            d.voiceTag = voicer.noteOn(d.noteNumber,gain);
            sDown = true;
        }
    }else if (key == 'd'){
        if (!dDown) {
            e.voiceTag = voicer.noteOn(e.noteNumber,gain);
            dDown = true;
        }
    }else if (key == 'f'){
        if (!fDown) {
            f.voiceTag = voicer.noteOn(f.noteNumber,gain);
            fDown = true;
        }
    }else if (key == 'g'){
        if (!gDown) {
            g.voiceTag = voicer.noteOn(g.noteNumber,gain);
            gDown = true;
        }
    }else if(key == 'h'){
        if (!hDown) {
            a.voiceTag = voicer.noteOn(a.noteNumber,gain);
            hDown = true;
        }
    }else if (key == 'j'){
        if (!jDown) {
            b.voiceTag = voicer.noteOn(b.noteNumber,gain);
            jDown = true;
        }
        
    }else if (key =='k'){
        if (!kDown) {
            c2.voiceTag = voicer.noteOn(c2.noteNumber,gain);
            kDown = true;
        }
    }else if (key == 'l'){
        if (!lDown) {
            d2.voiceTag = voicer.noteOn(d2.noteNumber,gain);
            lDown = true;
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    float gain = 50;
    switch (key) {
        case 'a':
            voicer.noteOff(c.voiceTag, gain);
            aDown = false;
            break;
        case 's':
            voicer.noteOff(d.voiceTag, gain);
            sDown = false;
            break;
        case 'd':
            voicer.noteOff(e.voiceTag, gain);
            dDown = false;
            break;
        case 'f':
            voicer.noteOff(f.voiceTag, gain);
            fDown = false;
            break;
        case 'g':
            voicer.noteOff(g.voiceTag, gain);
            gDown = false;
            break;
        case 'h':
            voicer.noteOff(a.voiceTag, gain);
            hDown = false;
            break;
        case 'j':
            voicer.noteOff(b.voiceTag, gain);
            jDown = false;
            break;
        case 'k':
            voicer.noteOff(c2.voiceTag, gain);
            kDown = false;
            break;
        case 'l':
            voicer.noteOff(d2.voiceTag, gain);
            lDown = false;
        default:
            break;
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

void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize ; i++) {
        float value = voicer.tick();
        output[2*i] = value;
        output[2*i+1] = value;
    }
}
