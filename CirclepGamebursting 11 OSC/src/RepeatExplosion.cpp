//   CREATE ALL THE EXPLOSIONS OF TINY CIRCLES EMITTED WHEN THE BIG BUBBLES ARE BURST :
//
//   ALLOWS YOU TO CREATE ANOTHER SET OF EXPLOSIONS  ( CAN BE MORE THAN 1 EXPLOSION ON SCREEN)
//
//   THEY HAVE INITIAL SPEED AND A RANDOM GRAVITY BETWEEN (0,mAcceleration)
//
//
//    THIS IS 1 GROUP OF EXPLOSION CIRCLES: THERE CAN BE MANY AT ONCE
//
//   EACH EXPLOSION CONSISTS OF  "maxCirles" OF CIRCLES.
//
//






#include "RepeatExplosion.h"

//--------------------------------------------------------------
void RepeatExplosion::setup(int mX,int mY){
//
//
//   SET UP EXPLOSION CIRCLES GROUP WITH GRAVITY  ALL WITH DIFF. INTITIAL VEL/ACC/RADIUS AND NUMBER (maxCirles)
//
//
//
//
//
//
//
 //ofBackground(255);
    //void setup(int mX,int mY,float mRadius,float mVelocity,float mAcceleration,int maxCircles);
    float myRadius=ofRandom(0,3);
    float myVelocity=ofRandom(0,25);
    float myAcceleration=ofRandom(0,-6);
    int maxCirles=ofRandom(30);
   
    //MAX CIRCLES SET UP ANOTHER SET OF CIRCLES TO EXPLODE
    //controlExplode.setup(ofGetWidth()/2,ofGetHeight()/2,myRadius,myVelocity,myAcceleration,maxCirles);
     controlExplode.setup(mX,mY,myRadius,myVelocity,myAcceleration,maxCirles);
}

//--------------------------------------------------------------
void RepeatExplosion::update(){
//
//
//   UPDATE KINEMATICS FOR DISPLAY
//
//
//
//
//
//
//
//
    controlExplode.update();

}

//--------------------------------------------------------------
void RepeatExplosion::draw(){
//
//
//   UPDATE KINEMATICS FOR DISPLAY
//
//
//
//
//
//
//
//
     controlExplode.draw();

}


