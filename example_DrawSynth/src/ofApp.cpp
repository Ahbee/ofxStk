#include "ofApp.h"

using namespace stk;

const float NoteC = 65.41;
const float NoteD = 73.42;
const float NoteE = 82.41;
const float NoteF = 87.31;
const float NoteG = 98.0;
const float NoteA = 110.0;
const float NoteB = 123.47;
const float NoteC2 = 130.81;
const float NoteD2 = 146.83;

//--------------------------------------------------------------
void ofApp::setup(){
    ofNoFill();
    ofSetLineWidth(3.0);
    drawRegion.set(200, 200, 700, 500);
    instructions.loadFont("verdana.ttf", 20);
    
    gui.setup("Settings");
    gui.add(attack.setup("attack(ms)",10,10,2000));
    gui.add(decay.setup("decay(ms)",200,10,2000));
    gui.add(sustain.setup("sustain",1,0,1));
    gui.add(release.setup("release(ms)",500,10,2000));
    gui.add(gain.setup("gain",.5,0,1));
    
    drawSynth.setAttack(attack/1000.0);
    drawSynth.setDecay(decay/1000.0);
    drawSynth.setSustain(sustain);
    drawSynth.setRelease(release/1000.0);
    drawSynth.setGain(gain);
    
    attack.addListener(this, &ofApp::adsrChanged);
    decay.addListener(this, &ofApp::adsrChanged);
    sustain.addListener(this, &ofApp::adsrChanged);
    release.addListener(this, &ofApp::adsrChanged);
    gain.addListener(this, &ofApp::adsrChanged);
    
    ofSoundStreamSetup(2, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 255, 0);
    ofRect(drawRegion);
    ofSetColor(0, 0, 0);
    ofLine(drawRegion.x, drawRegion.y + drawRegion.height/2, drawRegion.x + drawRegion.width, drawRegion.y + drawRegion.height/2);
    ofSetColor(255, 0, 0);
    wave.draw();
    
    ofSetColor(255,255,255);
    instructions.drawString("Use mouse to draw inside the green rectangle.\nPress a,s,d,f,g,h,j,k,l to play your wave", 300, 100);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // openframeworks calls keyPressed() even when key is heldDown
    // so we have check if key is already held down before calling noteOn
    if (key == 'a') {
        if (!aDown) {
            drawSynth.noteOn(NoteC, gain);
            aDown = true;
        }
    }else if (key == 's'){
        if (!sDown) {
            drawSynth.noteOn(NoteD, gain);
            sDown = true;
        }
    }else if (key == 'd'){
        if (!dDown) {
            drawSynth.noteOn(NoteE, gain);
            dDown = true;
        }
    }else if (key == 'f'){
        if (!fDown) {
            drawSynth.noteOn(NoteF, gain);
            fDown = true;
        }
    }else if (key == 'g'){
        if (!gDown) {
            drawSynth.noteOn(NoteG, gain);
            gDown = true;
        }
    }else if(key == 'h'){
        if (!hDown) {
            drawSynth.noteOn(NoteA, gain);
            hDown = true;
        }
    }else if (key == 'j'){
        if (!jDown) {
            drawSynth.noteOn(NoteB, gain);
            jDown = true;
        }
        
    }else if (key =='k'){
        if (!kDown) {
            drawSynth.noteOn(NoteC2, gain);
            kDown = true;
        }
    }else if (key == 'l'){
        if (!lDown) {
            drawSynth.noteOn(NoteD2, gain);
            lDown = true;
        }
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
    
    // have to do this check to allow legato style playing
    if (noNotesDown()) {
        drawSynth.noteOff(.5);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (drawRegion.inside(x, y)) {
        if (!drawingBegan) {
            wave.clear();
            drawingBegan = true;
        }
        if (wave.size() == 0 && x != drawRegion.x ) {
            wave.addVertex(drawRegion.x,y);
        }
        cutWaveToPoint(ofPoint(x,y));
        wave.addVertex(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (drawRegion.inside(x, y)) {
        drawingBegan = true;
        if (wave.size() != 0) {
            wave.clear();
        }
        if (x != drawRegion.x) {
            wave.addVertex(drawRegion.x,y);
        }
        cutWaveToPoint(ofPoint(x,y));
        wave.addVertex(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (drawingBegan) {
        ofPoint lastPoint = wave.getVertices().back();
        if (lastPoint.x < drawRegion.x + drawRegion.width) {
            wave.addVertex(drawRegion.x + drawRegion.width,lastPoint.y);
        }
        StkFrames frames = createWaveTableFromDrawing();
        drawSynth.setWaveTable(frames);
    }
    drawingBegan = false;
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

bool ofApp::noNotesDown() const{
    if (!(aDown || sDown || dDown || fDown || gDown || hDown || jDown || kDown || lDown)) {
        return true;
    }else{
        return false;
    }
}

//--------------------------------------------------------------

void ofApp::adsrChanged(float &val){
    drawSynth.setAttack(attack/1000.0);
    drawSynth.setDecay(decay/1000.0);
    drawSynth.setSustain(sustain);
    drawSynth.setRelease(release/1000.0);
    drawSynth.setGain(gain);
}

//--------------------------------------------------------------

void ofApp::cutWaveToPoint(ofPoint cutPoint){
    vector<ofPoint> &points = wave.getVertices();
    ofPoint lastPoint = points.back();
    while (lastPoint.x > cutPoint.x) {
        points.pop_back();
        lastPoint = points.back();
    }
}

//--------------------------------------------------------------

stk::StkFrames ofApp::createWaveTableFromDrawing(){
    int numberOfFrames = 5000;
    stk::StkFrames frames(numberOfFrames,1);
    for (int i = 0; i < numberOfFrames; i++) {
        float xValue = ofMap(i, 0, numberOfFrames-1, drawRegion.x, drawRegion.x+drawRegion.width);
        const vector<ofPoint> &points = wave.getVertices();
        float lerpPercentage;
        float firstVal;
        float secondVal;
        float yValue;
        for (int j = 0; j < wave.size()-1; j++) {
            firstVal = points[j].x;
            secondVal = points[j+1].x;
            if (xValue >= firstVal && xValue <=secondVal) {
                lerpPercentage = (xValue-firstVal)/(secondVal - firstVal);
                ofPoint newPoint = points[j].interpolated(points[j+1], lerpPercentage);
                yValue = transformYValue(newPoint.y);
                break;
            }
        }
        frames[i] = yValue;
    }
    return frames;
}

//--------------------------------------------------------------

float ofApp::transformYValue(float yValue) const{
    return -ofMap(yValue, drawRegion.y, drawRegion.y + drawRegion.height, -1, 1);
}

//--------------------------------------------------------------

void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++) {
        float value = drawSynth.tick();
        output[2*i] = value;
        output[2*i+1] = value;
    }
}


