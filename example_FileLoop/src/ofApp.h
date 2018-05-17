#pragma once

#include "ofMain.h"
#include "ofxStk.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void audioOut(ofSoundBuffer& buffer);
    void chorusParametersChanged(float &value);
    void reverbParametersChanged(float &value);
    void frequencyChanged(float &value);
    void filterCutoffChanged(float &value);
    
    ofxPanel panel;
    ofxFloatSlider frequency;
    ofxFloatSlider chorusDepth;
    ofxFloatSlider chorusFrequency;
    ofxFloatSlider reverbRoomSize;
    ofxFloatSlider filterCutoff;
    ofxToggle reverbOn;
    ofxToggle chorusOn;
    
    stk::FileLoop beat;
    stk::FreeVerb reverb;
    stk::Chorus chorus;
    stk::OneZero filter;
    
    ofSoundStream soundStream;
    
    ofTrueTypeFont instructions;
    bool shouldPlayAudio;
};
