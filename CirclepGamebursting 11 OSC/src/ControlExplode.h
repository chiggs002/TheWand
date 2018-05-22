#pragma once

#include "ofMain.h"
#include "ExplodeCircle.h"


class ControlExplode : public ofBaseApp{

	public:
		void setup(int mX,int mY,float mRadius,float mVelocity,float mAcceleration,int maxCircles);
        void addone(int mX,int mY);
        void update();
        void draw();
    void circleboundaries();

		
    
    vector <ExplodeCircle> explodeCircles;
    float myRadius;
    float myVelocity;
    float myAcceleration;
		
};
