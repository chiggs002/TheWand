//
//  This code creates ALL THE CIRCLES EMITTED FROM THE WAND
//
//  Reqires the file:
//
//  "IFRARED TRACKING 03 osc" to recieve position inputs
//  from a infrared sensor. Data is recieevd via OSC
//
//
//   ALL CIRCLES ARE EMITTED WITH NO FORCE BUT ALL HAVE A INITAL RANOM VELOCITY AND RADIUS
//
//
//   BAISC OPERATION:
//
//   A count down until a new game begins tells the user that a new game will commence in 'X' SECONDS (10 secs max)
//
//   PREVOUS SCORES ARE SHOWN IF THEY EXIST AND INSTRUCTIONS ON BUBBLE CREATION ARE GIVEN.
//
//   ANY TIME AFTER THE GAME BEIGNS AND THE WAND GOES OVER A BUBBLE IT IS DELETED AND THE SCORE IS UPDATE FOR THE USER
//
//   IF THE BUBBLES ESCAPE THE SCREEN DISPLAY A POINT IS GIVEN TO THE COMPUTER
//
//   SeperateCircles.cpp
//   Circlepacking
//
//
//
//  Created by CH on 17/03/2018.
//


//
//  SeperateCircles.cpp
//  Circlepacking
//
//  Created by CH on 17/03/2018.
//






#include "ofApp.h"
#include "ofxOsc.h"
#include "Circle.h"

//--------------------------------------------------------------
void ofApp::setup(){
//
//
//   SETUP INITIAL CIRCLES ON SCREEN: DEFAULT NUMBER
//
//
//   SETUP OSC TO RECEIVE MESSAGES
//
//
//
//
//
//
//
//
    
    //counter delay
    counterSlowdown =0;
    counterDelay=0;
    
    // set up osc receiver
    receiver.setup(PORT);
    
    markerX=0;
    markerY=0;
    
    // max number of bubble control
    randomMaxBubbles=int(ofRandom(280,340));
    ofBackground(255);
    // setup(int mX,int mY,float velMax,int maxCircles, int bursttime)
    separateCircles.setup(ofGetWidth()/2,ofGetHeight()/2,0.6,6,3000);
}

//--------------------------------------------------------------
void ofApp::update(){
//
//
//  UPDATE ALL EXPLOSION GRAPHICS AND CIRCLES WITH NEW POSITIONS
//
//
//
//
//
//
//
//
    
    separateCircles.update();
    repeatExplosions.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//
//
//  UPDATE ALL FORCES ON THE CIRCLES
//
//   INCREMENT COUNTER DELAYS
//
//   RECIEVE OSC GRAPHICS
//   DRAW INFRARED CIRCLE ON SCREEN
//   DRAW ALL CIRCLES ON SCREEN
//   DRAW ALL EXPLOSIONS ON SCREEN
    
    //receieve data always
    counterDelay++;
    if (counterDelay % 2==0) {
    counterDelay=0;
   // oscRecieve();
    }
      oscRecieve();

    
    // draw infrared marker showing current position
    ofPushStyle();
    ofSetColor(60, 90, 255);
    ofNoFill();
    ofSetLineWidth(3);
    ofDrawCircle(markerX,markerY,40);
    ofPopStyle();
  
    //Get the current position of infrared sensor
//     markerX=ofClamp(ofGetMouseX(), 0, ofGetWidth());
//      markerY=ofClamp(ofGetMouseY(), 0, ofGetHeight());
//      markerX=ofClamp(markerX, 0, ofGetWidth());
//     markerY=ofClamp(markerY, 0, ofGetHeight());
//     cout  <<"markerX "<<markerX<<"markerY= "<<markerY<<endl;
    
    //draw the bubbles
    separateCircles.draw(markerX,markerY);
    //make them explode
    repeatExplosions.draw();
}

//--------------------------------------------------------------


//--------------------------------------------------------------



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//
//
//  NOT USED WITH INFRARED SENSOR
//
//  USED TO DEBUG SYSTEM
//
//
//
//
//
//
   // markerX=ofGetMouseX();
   // markerY=ofGetMouseY();
    /*
    if ( ofGetElapsedTimeMillis() > separateCircles.newGameTime  ) {
        
        if (separateCircles.bubblesKilled < 10) {
        separateCircles.addone(markerX,markerY,int(ofRandom(2000,5000)));
       }//end if
        
    } //endif
     */
}



void ofApp:: oscRecieve () {
    // THE BASIC FUNCTION WAS FROM A CLASS EXERCISE ON OSC
    //
    //
    //
    // RECEIVING INFRARED DATA OF WAND POSITION FROM FILE:
    // "IFRARED TRACKING 03 osc"
    //
    //
    //
    //
    //
    
    if (messageBuffer.size()>maxBufferSize) messageBuffer.pop_back();
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        //
        // m.setAddress("/infrared/position");
        //m.addIntArg(x);
       // m.addIntArg(y);
       
        // check for mouse moved message
        if(m.getAddress() == "/infrared/position"){
        //    cout<<"MESSAGE RECEIVED"<<endl;
          //  cout<<"m.getArgAsInt(0)= "<<m.getArgAsInt(0)<<"   m.getArgAsInt(1)= "<<m.getArgAsInt(1)<<endl;
            // both the arguments are ints
           // mouseX = m.getArgAsInt(0);
           // mouseY = m.getArgAsInt(1);
            
          //  int markerX=ofGetMouseX();
          //  int markerY=ofGetMouseY();
            //1280,760
            
             markerX=m.getArgAsInt(0);
             markerY=m.getArgAsInt(1);
           cout<<"markerX= "<<markerX<<"   markerY= "<<markerY<<endl;
            
            if ( ofGetElapsedTimeMillis() > separateCircles.newGameTime  ) {
             
            //control the number of bubbles made
                
                // LIMIT NUMBER OF BUBBLES WITH  "randomMaxBubbles"
                if (separateCircles.circles.size() < randomMaxBubbles && separateCircles.bubblesKilled < 10) {
                 
                    if (( markerX > 10 && markerX < 1260) && ( markerY > 10 && markerY < 740)) {
                      // separateCircles.addone(markerX,markerY,int(ofRandom(2000,5000)));
                        counterSlowdown++;
                if (counterSlowdown%2==0)separateCircles.addone(markerX,markerY,int(ofRandom(2000,5000)));
                    }
                }//end if
                
            } //endif
            
         
            
              //  }//end if
                
           // } //endif
        
        
        } else {
            // unrecognized message: display on the bottom of the screen
            messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
        }
        
    } // while loop
    
}// osc recieved




