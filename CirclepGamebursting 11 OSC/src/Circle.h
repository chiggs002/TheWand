#pragma once

#include "ofMain.h"

class Circle : public ofBaseApp{

	public:
        //Circle(float x, float y,float rad,float velmax);
		void setup(float x, float y,float rad,float velmax,int bursttime,int r,int g, int b);
		void update();
		void draw();
        void drawWobbly();
        void drawNormal();
        void keyPressed(int key);

        //points on the circle
        vector <float> noiseSeeds;
        vector <ofPoint> saveValue;
        int noPointsUsed;
        float angleStep;
        float stepSize;
        float radius;
    
    
        // points
        ofPoint sunLoc;
        ofVec2f position;
        ofVec2f velocity;
        ofVec2f acceleration;
        int myr,myg,myb;
    
        float increm;
        float incremDir;
    // timer to burst
    Boolean canBurst;
    int burstInterval,burstTime;
   
    
    
};
