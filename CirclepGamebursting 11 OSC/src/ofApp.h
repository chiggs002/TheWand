#pragma once

#include "ofMain.h"
#include "SeparateCircles.h"
#include "RepeatExplosion.h"
#include "ofxOsc.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void oscRecieve();

		
		void mouseMoved(int x, int y );
		
    
    
     SeparateCircles separateCircles;
     RepeatExplosion repeatExplosions;
    
    int markerX;
    int markerY;
    // set osc
    ofxOscReceiver receiver;
    deque<string> messageBuffer;
    int maxBufferSize=20;
    int randomMaxBubbles;
    int counterDelay,counterSlowdown;
		
};
