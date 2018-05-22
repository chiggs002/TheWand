//   CREATE ALL THE CIRCLES EMITTED :
//  EVERY CIRCLE HAS A DIFF. COLOUR SIZE AND INITIAL SPEED
//
//
//
//
//
//
//
//




#include "Circle.h"

//Circle::Circle(float x, float y,float rad,float velmax) {
//
//    position.set(x, y);
//    velocity.set(ofRandom(-velmax,velmax), ofRandom(-velmax,velmax));
//    acceleration.set(0, 0);
//    radius = rad;
//
//}
//--------------------------------------------------------------
void Circle::setup(float x, float y,float rad,float velmax,int bursttime,int r,int g, int b){
    //  INITIALISE ALL VARIABLES
    //   EMIT CIRCLES WITH RANDOM RADIUS "RAD"
    //   EMIT CIRCLES WITH RANDOM VELOCITY
    //   EMIT CIRCLES WITH RANDOM COLOR
    //
    //
    //
    //
    //
    
    
    
    
    // SETUP TIMER BEFORE WE CAN BURST A BUBBBLE
    canBurst=false;
    burstInterval=2000;
    burstTime= ofGetElapsedTimeMillis()+burstInterval;
    
    
    //VARIABLES FOR COLOR IF USED
    ofPushStyle();
    myr=r;
    myg=g;
    myb=b;
    ofSetColor(ofColor::fromHsb(g,200,100),120);
    
    ofPopStyle();
    
    // RANDOMLY CHOOSE A DIRECTION FOR EVERY PARTICLE AND ROTATE THEM THEM CONTINOUSLY
    // RANDOMLY SETUP THE INTIAL VELOCITIES OF PARTICLES IF THEY DONT REQIURE A FORCE
    increm = ofRandom(-1,1);
    incremDir = ofRandom(-1,1);
    position.set(x, y);
    velocity.set(ofRandom(-velmax,velmax), ofRandom(-velmax,velmax));
    acceleration.set(0, 0);
    radius = rad;
   // cout<<"radius= "<< radius<<endl;
    //
    ofBackground(255);
    
    //
    // MAKING WOBBLY CIRCLES: HOW MANY POINTS? HOW BIG ARE THEY DEFORMED "stepSize"
    noPointsUsed = ofMap(radius,2,50,20,35);//40
    stepSize = ofMap(radius,2,50,5,20);//20;
    //position.set(400,400);
    //radius = 300;
    //radius = 2 + ofNoise(position.x*0.01, position.y*0.01) * 50;
    
    // WHATS THE ANGLE TO STEP OVER THE "CIRCLE"
    angleStep = 360.0 / noPointsUsed;
   
    //SETUP RANDOM SEEDS TO DEFORM A CIRCLE SURFACE
    ofSetCircleResolution(60);
    //setup random seeds
    for (int x=0; x<noPointsUsed; x++)
    {
        noiseSeeds.push_back(ofRandom(10000));
    }
}

//--------------------------------------------------------------
void Circle::update(){
    // JUST ROTATE A WOBBLY CIRCLE IF USED
    increm= increm+ incremDir;
    
    // UPDATE ALL VECTORS IN PLAY ACCELERATION + VELOCITY AND POSITION
    velocity = velocity + acceleration;
    position =  position + velocity;
    //cout<<"position= "<< position<<endl;
    acceleration.set(0,0);

}

void Circle::draw() {
    // EITHER DRAW PERFECT CICRLES OR WOBBLY ONES
    
    
    // can we burst the bubbles ?
    // EVREY BUBBLE HAS A NON DETRUCT INITIAL TIME
    if ( ofGetElapsedTimeMillis() > burstTime) {
        canBurst=true;
    }
    
   // drawNormal();
   drawWobbly();
    
}

void Circle::drawNormal() {
//
// JUST DRAW CIRCLES
//
//
//
//
//
//
    ofPushMatrix();
    // update
    ofTranslate(position.x,position.y);
    ofRotate(increm);
    //cout<<"increm= "<< increm <<endl;
    ofNoFill();
    ofSetColor(0);
    ofDrawCircle(0, 0, 0, radius);
    ofPopMatrix();
    

}

//--------------------------------------------------------------
void Circle::drawWobbly(){
// MAKE WOBBLY CIRCLES
// TOOK "noiseSeeds[i]" FROM CLASS WORK
//
// THE REST OF THE FUNCTION IS MINE
//
// saveValue WAS USED TO CLOSE THE BUBBLES
//
//
    
    
//  cout<<"radius= "<< radius<<endl;
    ofPolyline polyline;
    ofPushMatrix();
    // update
    ofTranslate(position.x,position.y);
    ofRotate(increm);
   // cout<<"increm= "<< increm <<endl;
    ofNoFill();
    ofSetLineWidth(3);
  
    //ofSetColor(myr,myg,myb);
    //ofSetColor(myr,myg,myb,120);
    ofSetColor(0,0,0);
    
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
} //END DRAW WOBBLY CIRCLE





void Circle::keyPressed(int key)
{

}

