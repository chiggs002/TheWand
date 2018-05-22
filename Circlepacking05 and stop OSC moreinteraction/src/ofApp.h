

#pragma once

#include "ofMain.h"
#include "SeparateCircles.h"

// INCLUDE OSC FOR THE WAND
#include "ofxOsc.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void erasecircles();
        void restart(int x, int y);
        int insidebox(int posx,int posy, int rx, int ry, int width, int height);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
    
       void oscRecieve();
       void insidebox(int x, int y);
		
    ofTrueTypeFont myfontBold;
    ofTrueTypeFont myfontReg;
    
    SeparateCircles separateCircles;
    int markerX;
    int markerY;
    int inside;
    ofColor myCol;
    int rr,gg,bb;
    int  counterErase;
    int programOnoff;
    int pushForceOnoff;
    int myDelay;
    
    // set osc
    ofxOscReceiver receiver;
    deque<string> messageBuffer;
    int maxBufferSize=20;
    int randomMaxBubbles;
    int counterDelay;
    int counterSlowdown;
   // ofTrueTypeFont myfontBold;
    ofTrueTypeFont *myFont;

		
};
