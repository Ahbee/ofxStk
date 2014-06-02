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
    
    void audioOut(float *output,int bufferSize,int nChannels);
    
    ofxPanel panel;
    ofxFloatSlider frequency;
    ofxFloatSlider chorusDepth;
    ofxFloatSlider chorusFrequency;
    ofxFloatSlider reverbRoomSize;
    ofxToggle reverbOn;
    ofxToggle chorusOn;
    
    stk::FileLoop beat;
    stk::FreeVerb reverb;
    stk::Chorus chorus;
    
    ofTrueTypeFont instructions;
    bool shouldPlayAudio;
};
