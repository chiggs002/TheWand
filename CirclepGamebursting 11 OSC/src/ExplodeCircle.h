#pragma once

#include "ofMain.h"

class ExplodeCircle : public ofBaseApp{

	public:
       // Circle(float x, float y,float rad,float velmax);
		void setup(float x, float y,float radmax,float velmax,float accelmax);
    
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
    
    
};
