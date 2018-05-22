#pragma once

#include "ofMain.h"

class Circle : public ofBaseApp{

	public:
        //Circle(float x, float y,float rad,float velmax);
		void setup(float x, float y,float rad,float velmax,int r,int g, int b);
		void update();
		void draw();
        void drawWobbly();
        void drawNormal();
    
        void keyPressed(int key);
    
        // new
        void tradForce();
        void nontradForce();
        void addForce(ofVec2f addforce);
        void sinRad();
        void noiseRad();


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
    
        float increm;
        float incremDir;
        int r,g,b;
       int sinCounter;
   
    
    
};
