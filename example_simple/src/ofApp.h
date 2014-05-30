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
    
    void audioOut(float *output,int bufferSize,int nChannnels);
    bool noNotesDown();
    
    ofxPanel gui;
    ofxFloatSlider op4Feedback;
    ofxFloatSlider op3Gain;
    ofxFloatSlider lfoSpeed;
    ofxFloatSlider lfoDepth;
    
    stk::BeeThree synth;
    
    ofTrueTypeFont intructions;
    
    bool aDown;
    bool sDown;
    bool dDown;
    bool fDown;
    bool gDown;
    bool hDown;
    bool jDown;
    bool kDown;
    bool lDown;
		
};
