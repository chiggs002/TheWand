//   CREATE ALL THE EXPLOSION CIRCLES EMITTED :
//
//  EVERY CIRCLE HAS A DIFF. COLOUR SIZE AND INITIAL SPEED
//
//
//  ALL EXPLOSION CIRCLE  HAVE RANDOM RADIUS VELOCITY AND ACCEL SET.
//
//
//
//
//








#include "ExplodeCircle.h"

    

//--------------------------------------------------------------
void ExplodeCircle::setup(float x, float y,float radmax,float velmax,float accelmax){
//
//
//   SET UP EXPLOSION CIRCLES WITH GRAVITY  ALL WITH DIFF. INTITIAL VEL/ACC/RADIUS
//
//
//
//
//
//
//
//
    
    position.set(x, y);
    cout  <<"DESTINATION MOUSE POSITION "<<"mX = "<< position.x<<"mY = "<<position.y<<endl;

    velocity.set(ofRandom(-velmax,velmax), ofRandom(-velmax,velmax));
    acceleration.set(ofRandom(-velmax,velmax), ofRandom(-velmax,velmax));
    radius = ofRandom(0,radmax);
    
    
    //  ofBackground(255);
    
    // MAKING WOBBLY CIRCLES: HOW MANY POINTS? HOW BIG ARE THEY DEFORMED "stepSize"
    noPointsUsed = ofMap(radius,2,50,20,35);//40
    stepSize = ofMap(radius,2,50,5,20);//20;
    
    //position.set(400,400);
    //radius = 300;
    //radius = 2 + ofNoise(position.x*0.01, position.y*0.01) * 50;
    
    // WHATS THE ANGLE TO STEP OVER THE "CIRCLE"
    angleStep = 360.0 / noPointsUsed;
  
    //SETUP CIRCLE SMOOTHNESS
    ofSetCircleResolution(60);
    
    //SETUP RANDOM SEEDS TO DEFORM A CIRCLE SURFACE
    //setup random seeds
    for (int x=0; x<noPointsUsed; x++)
    {
        noiseSeeds.push_back(ofRandom(10000));
    }
}

//--------------------------------------------------------------
void ExplodeCircle::update(){
//
//   UPDATE KINEMATICS ACCELERATION VELOCITY AND POSITION
//   RESET ACCERLATION TO ZERO
//
//
   velocity= velocity + acceleration;
    position=  position + velocity;
    acceleration.set(0,0);

}

void ExplodeCircle::draw() {
//
//
//  DRAW A WOBBLY CIRCLE AT THE CURRENT POSITION
//
//
//
//
    // drawNormal();
    drawWobbly();
    
}

void ExplodeCircle::drawNormal() {
//
// JUST DRAW CIRCLES AT CURRENT POSITION
//
//
//
//
//
//
    
    ofPushMatrix();
    // update
    ofTranslate(position.x,position.y);
    ofNoFill();
    ofSetColor(0);
    ofDrawCircle(0, 0, 0, radius);
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------
void ExplodeCircle::drawWobbly(){
// MAKE WOBBLY CIRCLES AT CURRENT POSITION
//
//
//
// saveValue WAS USED TO CLOSE THE BUBBLES
//
// noiseSeeds[i] FROM A CLASS EXERCISE

    
    
    //  cout<<"radius= "<< radius<<endl;
    ofPolyline polyline;
    ofPushMatrix();
    // update
    ofTranslate(position.x,position.y);
    ofNoFill();
    ofSetColor(0);
    
    // ofSetColor(253, 202, 19);
    
    ofBeginShape();
    for (int i=0; i<noPointsUsed; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds[i]) * stepSize;
        float noisedRadius2 = radius-4 + ofNoise(noiseSeeds[i]) * stepSize;
        float valX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float valY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds[i]+=0.01;
        ofPoint value;;
        value[0]=valX;
        value[1]=valY;
        
        // Draws a curve through a series of vertices stored as a vector of ofPoints
        ofCurveVertex(valX, valY);
        
        
        // polyline.addVertex(value);
        saveValue.push_back(value);
        // ofVertex(endX, endY);
        
    }
    
    
    // CLOSE THE GAPS ON BUBBLES. USE THE SAVED VERTEX X,Y POSITIONS
    polyline.addVertex(saveValue[0]);
    polyline.addVertex(saveValue[noPointsUsed]);
    
    
    // polyline.draw();
    
    ofEndShape(true);
    
    // ofSetColor(255,215, 13);
    //ofCircle(0, 0, 300);
    
    ofPopMatrix();
}

void ExplodeCircle::keyPressed(int key)
{
    
}





