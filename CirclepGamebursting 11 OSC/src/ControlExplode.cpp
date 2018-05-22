//   CREATE ALL THE EXPLOSIONS OF TINY CIRCLES EMITTED WHEN THE BIG BUBBLES ARE BURST :
//
//   ALL CIRCLES HAVE A GRAVITATIONAL FORCE ON THEM AND A INITAL VELOCITY
//
//   THEY HAVE INITIAL SPEED AND A RANDOM GRAVITY BETWEEN (0,mAcceleration)
//
//
//
//
//







#include "ControlExplode.h"
#include "ExplodeCircle.h"


//--------------------------------------------------------------


   void ControlExplode::setup(int mX,int mY,float mRadius,float mVelocity,float mAcceleration,int maxCircles){
//
//
//  SETUP CEXPLOSION CICLRES WITH RANDOM RADIUS,VELOCITY,ACCLELEATION AND NUMBER OF CIRCLES WE USE (maxCircles)
//
//
//
//
//
//
       // explodeCircles.resize(maxCircles);
       
       //SETUP RANDOM PARTICLES WITH ALL DIFF RADIUS/VELOCITY/ACCELERATION
       myRadius=ofRandom(0,mRadius);
       myVelocity=ofRandom(1,mVelocity);
       myAcceleration=ofRandom(0,mAcceleration);
       //cout<<"myRadius= "<<myRadius<<endl;
       
       
      
       
      //  ofBackground(255);
       
       // for(int i=0; i<explodeCircles.size(); i++){
       
       
       // ALL CIRCLES HAVE A GRAVITATIONAL FORCE ON THEM AND A INITAL VELOCITY
       
       // MAX AMOUNT OF EXPLOSION CIRCLES IS RANDOMLY CHOSEN
        for(int i=0; i< maxCircles; i++){
            ExplodeCircle b;
            b.setup(mX,mY,myRadius,myVelocity,myAcceleration);
            explodeCircles.push_back(b);
            
            //setup(float x, float y,float radmax,float velmax,float accelmax){
           // float myRadius=ofRandom(0,3);
           // float myVelocity=ofRandom(1,3);
          //  float myAcceleration=ofRandom(7,10);
         
            //explodeCircles[i].setup(mX,mY,myRadius,myVelocity,myAcceleration);
        } //generate maxCircles
    
}

void  ControlExplode:: addone(int mX,int mY) {
// ADD A EXPLOSION CIRCLE WITH DIFFERENT PARAMETERS RADIUS/VELOCITY/GRAVITY
//
//
//
//
//
//
//
//
//
    
    //float myRadius=ofRandom(2,20);
   // cout<<"myRadius= "<<myRadius<<endl;
    
    ExplodeCircle b;
    float myRadius=ofRandom(0,3);
    float myVelocity=ofRandom(1,3);
    float myAcceleration=ofRandom(7,10);
    cout<<"myRadius= "<<myRadius<<endl;
    //explodeCircles[i].setup(mX,mY,myRadius,myVelocity,myAcceleration);
    b.setup(mX,mY,myRadius,myVelocity,myAcceleration);
    explodeCircles.push_back(b);
    
}



void  ControlExplode::update() {
// LET THE PARTICLE KINEMATICS PLAY OUT:
//
//  UPDATE THE PARTICLES ACCERERATION/SPEED AND POSITION
//
//
//
//
//
//
//
    
    
    //UPDATE KINEMATICS PARTICLES ACCERERATION/SPEED AND POSITION
    //
    for(int i=0; i<explodeCircles.size(); i++){
    //  explodeCircles[i].acceleration= ofVec2f(0,-1.0*myAcceleration);
        explodeCircles[i].update();
       // explodeCircles[i].acceleration= ofVec2f(0,-1.0*myAcceleration);

    }
}


void  ControlExplode:: draw() {
//
//
//  DRAW THE PARTICLES ON SCREEN AND RESET THE ACCELERATION AS IT IS ALWAYS ZEROED OUT
//
//
//
//
//
//
//
// cout<<"CURRENT PARTICLE SIZE= "<<explodeCircles.size()<< endl;
    
    //DRAW THE PARTICLES ON SCREEN AND RESET THE ACCELERATION AS IT IS ALWAYS ZEROED OUT
    for(int i=0; i<explodeCircles.size(); i++){
        explodeCircles[i].draw();
        explodeCircles[i].acceleration= ofVec2f(0,-1.0 *myAcceleration);
    }
    circleboundaries();
} //END DRAW



void ControlExplode::circleboundaries() {
//
//
//  DELETE ANY PARTICLES WHEN THEY LEAVE THE SCREEN
//
//  IMPORTANT TO DO OTHERWISE NEVERENDING PARTICLES MADE
//
//
//
//
//
    
    //cout <<"ARRAY  size BEFORW = " << explodeCircles.size() <<endl;
    for(int i=0; i<explodeCircles.size(); i++){
        
    if (explodeCircles[i].position.x <0 || explodeCircles[i].position.x > ofGetWidth()  ) {
        explodeCircles.erase(  explodeCircles.begin() + i );
       //  cout <<"element deleted current size = " << explodeCircles.size() <<endl;
    }
        if (explodeCircles[i].position.y <0 || explodeCircles[i].position.y > ofGetHeight()  ) {
            explodeCircles.erase(  explodeCircles.begin() + i );
         //   cout <<"element deleted current size = " << explodeCircles.size() <<endl;
        }
        
   
    }//loopround circles
}


