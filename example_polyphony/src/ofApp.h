#pragma once

#include "ofMain.h"
#include "ofxStk.h"

struct MusicalNote {
    stk::StkFloat noteNumber;
    long voiceTag;
};

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
    
    stk::Voicer voicer;
    
    MusicalNote c,d,e,f,g,a,b,c2,d2,e2;
    
    bool aDown;
    bool sDown;
    bool dDown;
    bool fDown;
    bool gDown;
    bool hDown;
    bool jDown;
    bool kDown;
    bool lDown;
    
    ofTrueTypeFont instructions;
		
};
