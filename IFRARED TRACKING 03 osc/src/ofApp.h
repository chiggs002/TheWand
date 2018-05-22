// Example 3. Finding the Brightest Pixel in an Image

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    float lowPassAveraging(double input, int points );
    void InfraredMoved(int x, int y);
    
    // Replace this ofImage with live video, eventually
    ofVideoGrabber vidGrabber;
    float closestColorX, closestColorY;
    float lastclosestColorX, lastclosestColorY;
    float sumclosestColorX, sumclosestColorY;
    
    void mousePressed(int x, int y, int button);
    float rTarget;
    float gTarget;
    float bTarget;
    float threshold;
    void keyPressed(int key);
    int count;
    float x[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    ofxOscSender sender;
};
