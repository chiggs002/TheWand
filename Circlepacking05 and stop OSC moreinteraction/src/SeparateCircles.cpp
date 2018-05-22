//
//  This code creates a live Circle Packing Algorithm
//
//  Reqires the file:
//
//  "IFRARED TRACKING 03 osc" to recieve position inputs
//  from a infrared sensor. Data is recieevd via OSC
//
//
//  This work is based the study of Daniel Shiffmans work on circle packing:
//  https://www.youtube.com/watch?v=QHEQuoIKgNE
//
//  And also his basic flocking algorithms:
//  https://www.youtube.com/watch?v=JIz2L4tn5kM&list=PLRqwX-V7Uu6YHt0dtyf4uiw8tKOxQLvlW
//
//  SeperateCircles.cpp
//  Circlepacking
//
//
//
//  Created by CH on 17/03/2018.
//


#include "SeparateCircles.h"
#include "Circle.h"



void  SeparateCircles:: setup(int mX,int mY,float velMax,int maxCircles) {
// INITALISE ALL VARIABLES FOR BOTH CIRCLES AND WOBBLY CIRCLES
    
   
    // MAX SEPARATION FORCE AND SPEED
    maxSpeed=1;
    maxForce=1;
   
  
    //   SET UP HOW MANY INITIAL CIRCLES/WOBBLY CIRCLES WITH: maxCircles
    for(int i=0; i<maxCircles; i++){
        int r=ofRandom(255);
        int g=ofRandom(250);
        int bb=ofRandom(235);
        //cout<<"r= "<<r<<endl;
        // RANDOMLY INITIALISE RADIUS OF EACH CIRCLE
        float myRadius=ofRandom(2,20);
        //cout<<"myRadius= "<<myRadius<<endl;
        
        
        // CREATE A CIRCLE CLASS WITH DIFFERENT RADIUS AND VELOCITIES
        // USE A VECTOR ARRAY
        Circle b;
        b.setup(mX,mY,myRadius,ofRandom(0.1,velMax),r,g,bb);
        circles.push_back(b);
        
        // cretae random push vector active if wand is inside the circle
        ofVec2f c(ofRandom(-maxForce,maxForce),ofRandom(-maxForce,maxForce));
        pushsepbetween.push_back(c);
        
    } //generate maxCircles
}






void  SeparateCircles:: addone(int mX,int mY) {
//  ADD ON A SINGLE CIRCLE WITH RANDOM RADIUS AND VELOCITY
//  USE THE WAND POSITION mX,mY OBTAINED WITH OSC
//
//
    float myRadius=ofRandom(2,20);
    //cout<<"myRadius= "<<myRadius<<endl;
    
    Circle b;
    b.setup(mX,mY,myRadius,ofRandom(0.1,1.3),ofRandom(255),ofRandom(255),ofRandom(255));
    circles.push_back(b);
    
    
     // cretae random push vector active if wand is inside the circle
    
    ofVec2f c(ofRandom(-maxForce,maxForce),ofRandom(-maxForce,maxForce));
    pushsepbetween.push_back(c);
    
   
}



void  SeparateCircles::update() {
//  EITHER SEPARATE THE BUBBLES CONTINUOUSLY OR TRY CIRCLEPACKING (goThruSeparationForce)
//
//  circles[i].tradForce()= NO CIRCLE PAKING THEY JUST SEPERATE
//
// EITHER THE CIRCLE RADIUS CHNAGE OVER TIME OR NOT:  circles[i].noiseRad()
//
//
//
//
    for(int i=0; i<circles.size(); i++){
        circles[i].update();
        // circles[i].tradForce();
        //circles[i].sinRad();
        
        // CHNAGE RADIUS OVER TIME
        circles[i].noiseRad();
        // CALL CIRCLE PACKING ALGORITHM
        goThruSeparationForce(i,circles);
    }
}






void  SeparateCircles:: draw(int mX,int mY,int pushforceActive) {
//
//
//
//  DRAW ALL THE CIRCLES ON SCREEN AT THEIR CURRENT POSITION
//
//  ARE THE CIRCLES INSIDE mX, mY CALL circleinside(mX, mY)
//
//  DELETE ANY CIRCLES OUTSIDE THE BOUNDARIES OF THE SETUP SIZE.
//
//
//
    
    
    
    for(int i=0; i<circles.size(); i++){
        circles[i].draw();
    }
    // identify circle with mpuse on them
  //  cout  <<"PASSED mouse x= "<<mX<<"PASSED mouse y= "<<mY<<endl;
     circleinside(mX, mY,pushforceActive);
    //delete any circle outside of boundaries
     circleboundaries();
}












void SeparateCircles::circleboundaries() {
//
// ARE THE CIRCLES INSIDE THE CURRENT IMAGE VIEWER?
//
// IF YES: DO NOTHING
// IF NO:  DELETE THEM
//
//
   // cout <<"circles ARRAY  size BEFORW = " << circles.size() <<endl;
    for(int i=0; i<circles.size(); i++){
        
        if (circles[i].position.x <0 || circles[i].position.x > ofGetWidth()  ) {
            circles.erase(  circles.begin() + i );
           // cout <<"circle element deleted current size = " << circles.size() <<endl;
        }
        if (circles[i].position.y <0 || circles[i].position.y > ofGetHeight()  ) {
            circles.erase( circles.begin() + i );
           // cout <<"circle element deleted current size = " << circles.size() <<endl;
        }
    }
} //circleboundaries








void SeparateCircles::circleinside(int x, int y,int pushforceActive) {
//
// AM I INSIDE ANY CIRCLE USING X,Y AS INPUTS ?
//
// IF YES: DELETE THEM
// IF NO:  DO NOTHING
//
// USE THE POSITION AND RADIUS OF THE CIRCLE TO ANWSER THIS QUESTION
//
//  OF YES APPLY  A PUSH FORCE TO CIRCLES - MOVE THEM RANDOMLY
//
    
    //cout <<"circles ARRAY  size BEFORW = " << circles.size() <<endl;
    for(int i=0; i<circles.size(); i++){
//        cout  <<"............................."<<endl;
//         cout  <<"............................."<<endl;
//         cout  <<"............................."<<endl;
//        cout  <<"circles.size() = ="<<circles.size()<<endl;
//        cout  <<"mouse x= "<<x<<"mouse y= "<<y<<endl;
//        cout  <<"position.x= "<<circles[i].position.x<<"position.y= "<<circles[i].position.y<<endl;
        float checkx= abs(circles[i].position.x-x);
       // cout <<"checkx = " <<checkx<<endl;
        float checky= abs(circles[i].position.y-y);
       // cout <<"checkx= " <<checky<<endl;
        if (checkx < circles[i].radius && checky < circles[i].radius  ) {
            //circles.erase(  circles.begin() + i );
            cout  <<"............................."<<endl;
            cout  <<"............................."<<endl;
            cout  <<"............................."<<endl;
             cout <<"INSIDE CIRCLE " <<endl;
            cout  <<"circles.size() = ="<<circles.size()<<endl;
             cout <<"checky= " <<checky<<endl;
            cout <<"checkx = " <<checkx<<endl;
            
            if (pushforceActive ==1) {
                
            calcPushForce(i);
                
                
            }//push circlesaway
            
        
        }// curclesinside true
    }
} //circleinside










ofVec2f SeparateCircles::calcSeparationForce(Circle c1, Circle c2 ) {
//    CALC. THE FORCE SEPARATION OF THE  PARTICLES
//
//    NORMALISE/DISTANCE== DANIEL SHIFFMAN DOES THIS FOR EASE IN ACCELERATION
//
//
//   THE FORCE IS BASED ON THE VECTORS SEPARATING
//   THEM AS THIS MEANS THE CIRCLES SEPARATE IN ALL OPPOSITE DIRECTIONS
//
//   OPPOSITE DIRECTIONS IS THE KEY TO THE SEPARATION
//
 
    
    // APPLY FORCE BASED ON OVERAPPING CIRCLES POSITIONS
    // CREATE A VECTOR OF THE OPPOSITE DIRECTION TO MOVE THEM APART
    
    
    ofVec2f direction(0, 0);
    float distance = c1.position.distance( c2.position );
    //  cout<<"DISTSANCE BETWEEN CIRCLES   ========"<<distance<<endl;
    
   //cout<<"radial distance between 2 circles  ========"<<c1.radius/2.0+c2.radius/2.0<<endl;
    
    //if the same position on top of each other
    if (distance ==0) {
        
        ofVec2f sepbetween(ofRandom(-maxForce,maxForce),ofRandom(-maxForce,maxForce));
        sepbetween.normalize();
        direction =  (sepbetween/distance)*10.0;
      //  cout<<"DIRECTION FORCE   ========"<<direction<<endl;
        return direction;
        
        
    }
    if  ( (distance < (c1.radius+c2.radius) ) ) {

       ofVec2f sepbetween= c1.position-c2.position;
        //cout<<"sepbetween   ========"<<sepbetween<<endl;
        sepbetween.normalize();
        direction =  (sepbetween/distance)*10.0;
       //  cout<<"DIRECTION FORCE   ========"<<direction<<endl;
        return direction;
    }//if less than combined raius
}//seperation force







void SeparateCircles::goThruSeparationForce(int i, vector <Circle> circ) {
// LOOP AROUND EVERY CIRCLE EXCEPT SELF AND SEE IF EACH CIRCLE IS TOUCHING.
//
// IF ANY CIRCLES OVERLAP CALC SEPARATION FORCE BASED ON THEIR CURRENT POSITION VECTOR.
// AS THIS MEANS THE SEPARATING FORCES WILL BE NEGATIVE TO EACH OTHER.
// EXACTLY WHAT IS NEEDED
//
// THE LIMIT ON THE SPEED IS FROM DANIEL SHIFFMAN
//
    Circle myCircle =circ[i];
    
    //gothru each circle only if i! =j
    for (int j=0; j< circ.size(); j++) {
         Circle otherCircle =circ[j];
        if (j!=i) {
            
       // calculate the seperation force for each pair of circles
            ofVec2f sepForce = calcSeparationForce (myCircle,otherCircle);
            // (magnitude) of this vector.
            float len = sepForce.length();
            if ( len > 0 ) {
                
           // LIMIT THE SPEED OFCHNAGE
             sepForce.limit(maxSpeed);
                
            }//if len > 0
            
            circles[i].addForce(sepForce);
            circles[i].nontradForce();
            // THE CALC. FORCE MUST BE RESET TO REUSE
            sepForce.set(0,0);

            
        }//gothru each circle only if i! =j
        
    } //gothru each circle only if i! =j
    
};

void SeparateCircles::calcPushForce(int i) {
    //    CALC. THE FORCE SEPARATION OF THE  PARTICLES
    //
    //
    //
    //
    //   THE PUSH FORCE IS BASED ON THE A RANDOM VECOR
    //
    //
    //
    
     ofVec2f direction(0, 0);
     //pushsepbetween.set(ofRandom(-maxForce,maxForce),ofRandom(-maxForce,maxForce));
    cout<<"PUSH VECROR VALUE="<<pushsepbetween[i]<<endl;
     pushsepbetween[i].normalize();
     direction =  pushsepbetween[i]*10.0;
    
    circles[i].addForce(direction);
    circles[i].nontradForce();
    // THE CALC. FORCE MUST BE RESET TO REUSE
   // pushsepbetween.set(0,0);
    
  
}//seperation force


