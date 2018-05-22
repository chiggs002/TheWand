#pragma once

#include "ofMain.h"
#include "ControlExplode.h"


class RepeatExplosion : public ofBaseApp{

	public:
		void setup(int mX,int mY);
		void update();
		void draw();

		
     ControlExplode controlExplode;
		
};
