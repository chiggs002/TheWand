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


//--------------------------------------------------------------
void Circle::setup(float x, float y,float rad,float velmax,int rr,int gg, int bb){
//   INITIALISE ALL VARIABLES
//
//
//
//
//
//
//
//
    
    // RANDOMLY SETUP THE INTIAL VELOCITIES OF PARTICLES IF THEY DONT REQIURE A FORCE
    increm = ofRandom(-1,1);
    incremDir = ofRandom(-1,1);
    position.set(x, y);
    velocity.set(ofRandom(-velmax,velmax), ofRandom(-velmax,velmax));
    acceleration.set(0, 0);
    radius = rad;
    sinCounter=0;
    //    ofSetColor(r,g,b,120);
  
    
    // SET UP A RANDOM COLOUR
    r=rr;
    g=gg;
    b=bb;
   // cout<<"radius= "<< radius<<endl;
    //
    ofBackground(255);
    
    // MAKING WOBBLY CIRCLES: HOW MANY POINTS? HOW BIG ARE THEY DEFORMED "stepSize"
    noPointsUsed = ofMap(radius,2,50,20,35);//40
    stepSize = ofMap(radius,2,50,5,20);//20;
    
    // WHATS THE ANGLE TO STEP OVER THE "CIRCLE"
    angleStep = 360.0 / noPointsUsed;
    
    //SETUP CIRCLE SMOOTHNESS
    ofSetCircleResolution(60);
    
    
    //SETUP RANDOM SEEDS TO DEFORM A CIRCLE SURFACE
    for (int x=0; x<noPointsUsed; x++)
    {
        noiseSeeds.push_back(ofRandom(10000));
    }
}

//--------------------------------------------------------------
void Circle::update(){
// JUST ROTATE A WOBBLY CIRCLE IF USED
   increm= increm+ incremDir;

}

void Circle::draw() {
// EITHER DRAW PERFCT CICRLES OR WOBBLY ONES
  drawNormal();
//drawWobbly();
    
}

void Circle::drawNormal() {
//
// JUST DRAW CIRCLES AT CURRENT POSITION
//
//
//
//
//
//
    ofPushStyle();
    ofPushMatrix();
    // update
    ofTranslate(position.x,position.y);
    ofRotate(increm);
    //cout<<"increm= "<< increm <<endl;
    ofNoFill();
    //ofSetColor(0);
    //ofSetColor(r,g,b,120);
    //ofPushStyle();
   
     // USE HUE SATURATION AND BRIGHTNESS TO DEFINE COLORS
    ofSetColor(ofColor::fromHsb(g,200,100),120);
    ofDrawCircle(0, 0, 0, radius);
    ofPopMatrix();
     ofPopStyle();
    

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
    //ofSetColor(0);
    
   // ofSetColor(253, 202, 19);

    ofBeginShape();
    
    //  noPointsUsed*angleStep=360 A CIRCLE.
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

void Circle::keyPressed(int key)
{

}

void Circle::tradForce() {
// CONTINIOUS  VELOCITY OF PARTICLES
// velocity != acceleration ONLY
//
// ALL PARTICLES HAVE INITIAL VELOCITY
//

    velocity = velocity + acceleration;
    position =  position + velocity;
    //cout<<"position= "<< position<<endl;
    acceleration.set(0,0);
}

void Circle::nontradForce() {
//  THE ONLY WAY PARTICLES MOVE IF THERE IS A FORCE
//  ACTING ON THEM. NO FORCE THEY STOP.
//
//
//
//
//
    
    velocity = acceleration;
    position =  position + velocity;
    //cout<<"position= "<< position<<endl;
    acceleration.set(0,0);
}

void Circle::addForce(ofVec2f addforce) {
//  ADD ANY FORCES TO THE ACCERERLATION
//
//
//
//
    acceleration=acceleration+addforce;
}


void Circle::sinRad() {
    // THIS WAS AN ACCIDENT THE ORIGINAL WORK
    // WAS WITH JUST INITIAL RANDOM RADIUS VALUES AT THE START.
    //
    //  WAS THINKING ABOUT HOW THE BUBBLES CHANGE SIZE OVER TIME
    //
    //
    //
    // SLOWLY CHNAGE RADIUS OF CIRCLES IF THEY ARE MOVING
    
    sinCounter++;
    radius = 3 + abs(sin(position.x*0.01 +position.x*0.01) ) * 40;
    
    
    
    
}






void Circle::noiseRad() {
// THIS WAS AN ACCIDENT THE ORIGINAL WORK
// WAS WITH JUST INITIAL RANDOM RADIUS VALUES AT THE START.
//
//  WAS THINKING ABOUT HOW THE BUBBLES CHANGE SIZE OVER TIME
//
//
//
// SLOWLY CHNAGE RADIUS OF CIRCLES IF THEY ARE MOVING
   // radius = 3 + ofNoise((position.x+increm/10.0)*0.01,(position.y+increm/10.0)*0.01) * 40;
    radius = 3 + ofNoise(position.x*0.01,position.y*0.01) * 40;
    

}



