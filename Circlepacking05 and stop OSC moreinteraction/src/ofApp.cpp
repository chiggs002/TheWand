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
//  Created by CH on 17/03/2018.
//
//
//
//
//  This code creates a live Circle Packing Algorithm
//
//  Reqires the file:
//
//  "IFRARED TRACKING 03 osc" to recieve position inputs
//  from a infrared sensor. Data is recieevd via OSC
//
//
//  BASIC OPERATATION:
//
//  The "RESTART" button basically deletes any circles on screen
//  and 2 seconds later circles can emanate from the wand position.
//
//  When any circles emanate from the wand position and overalap they automatically separate from themselves
//
//
//
//  Further user interaction has been add where the wand adds a push force on the circles if
//  the wand is inside the circle
//
//  Apart from the separation force algorithm all the code is mine
//









#include "SeparateCircles.h"
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //
    //
    //  SETUP INITIAL CIRCLES ON SCREEN: DEFAULT NUMBER
    //
    //
    //
    //
    //
    //
    //
    
    // INITIALIZE VARIABLES
    inside=0;
    rr=50;
    gg=0;
    bb=100;
    counterErase=0;
    myDelay=0;
    
    
    // set up osc receiver
    receiver.setup(PORT);
    
    
    //RESTART THE PROGRAM IF THE GAME HAS ENDED AND NO BUBBLES LEFT
    programOnoff=1;
    
    //push circles away from each other on ==1 off --0
    pushForceOnoff=0;

    
    // max number of bubble control
    randomMaxBubbles=int(ofRandom(200,340));
    
    
    markerX=0;
    markerY=0;
    counterSlowdown =0;
    ofBackground(255);
    
    
    // setup(int mX,int mY,float velMax,int maxCircles)
    
    // SETUP INITIAL CIRCLES
    separateCircles.setup(ofGetWidth()/2,ofGetHeight()/2,0.2,13);
    //myfontBold.load("DIN-Bold.otf",40);
    myfontReg.load("DIN-Regular.otf",40);
    myFont = new ofTrueTypeFont();
   // myFont->loadFont("DIN-Regular.otf", 20);

}

//--------------------------------------------------------------
void ofApp::update(){
//
//
//  UPDATE ALL FORCES ON THE CIRCLES
//
//
//
//
//
//
//
//
    separateCircles.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//
//
//  CHECK FOR INPUT DATA FROM INFRARED SENSOR
//
//  DRAW A "RESTART" BOX
//
//  IF THE WAND IS IN THE RESTART BOX DELETE ALL THE CIRCLES
//  WE HAVE ON DISPLAY AND RESTART THE SYSTEM TO DRAW NEW CIRCLES
//
//
//  UPDATE ALL CIRCLE POSITIONS ON SCREEN
//
    
    //RECIEVE INFRARED WAND POSITION DATA
    oscRecieve();
    ofPushMatrix();
    
    // DRAW A MARKER ( RECTANGLE FOR THE WAND )
    ofNoFill();
    ofSetColor(255,0,0);
    ofSetLineWidth(6);
    ofDrawRectangle(markerX, markerY,50, 50 );
    
    //SETUP RESTART BOX
    
     ofSetColor(rr, gg, bb,200);
    
  // ofSetColor(myr,myg, myb);
    ofFill();
    ofDrawRectangle(50, 20,150, 50 );
   // ofDrawRect(50, 20,150, 50);
    ofSetColor(255);
    
    string restart  = "RESTART";
    myfontBold.load("DIN-Bold.otf",20);
    myfontBold.drawString(restart, 65,55);
    
    // do we want to restart?
    //
   // markerX=ofGetMouseX();
   // markerY=ofGetMouseY();
    //cout <<" markerX= "<<markerX<<" markerY= "<<markerY<<endl;
    //int check = insidebox(markerX,markerY, 50, 20, 150, 50 );
    //cout<<"CHECK==== "<<check<<endl;
    
    
    // CALL A FUNCTION TO SEE IF WE WANT TO RESTART THE GAME.
    int check = insidebox(markerX,markerY, 50, 20, 150, 50 );
    
    // Are we hovering over the "restart" graphic?
    if (check==1) {
        // ERASE THE CICRLES
        erasecircles();
        
    }else {
        // COLOUR FOR RESET BOX IF WE DONT ERASE THE CIRCLES
        rr=50;
        gg=0;
        bb=100;
        
    }//wipeout circles
    
    
    ofPopMatrix();
    
//    // USE MOUSE AS INPUTS
//   markerX=ofClamp(ofGetMouseX(), 0, ofGetWidth());
//   markerY=ofClamp(ofGetMouseY(), 0, ofGetHeight());
    
   // cout  <<"markerX "<<markerX<<"markerY= "<<markerY<<endl;
    
   // USE THE WAND AS INITIAL INPUTS FOR THE CIRCLE POSITIONS
   // VIA OSC FILE:  SEE "IFRARED TRACKING 03 osc" FOR INPUTS
    
    
    // use a push force on the circles to shift around if we have the pushforce on
   separateCircles.draw(markerX,markerY,pushForceOnoff);
}



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // ADD MORE CIRCLES AT THE CURRENT MOUSE POSITION
    // NOT USED WITH THE INFRARED TRACKER
    markerX=ofGetMouseX();
    markerY=ofGetMouseY();
    separateCircles.addone(markerX,markerY);
    
    if (separateCircles.circles.size()>40) {
        // can push circles
        pushForceOnoff=1;
        
        // cant add more circles
        cout<<"pushForceOnoff*******************************"<<endl;
        cout<<"pushForceOnoff="<<pushForceOnoff<<endl;
        
    }//push force activate
}


int ofApp::insidebox(int posx,int posy, int rx, int ry, int width, int height) {
//
//
//   HAS THE WAND BEEN PLACED INSIDE THE "RESTART" BOX? YES OR NO
//
//
//
//
//
//
//
//
//
 
    //ofRect(50, 20,150, 50); x and y width and height
    inside=0;
    
    int topPosy= ry;
    int botPosy= ry+height;
    int leftPosx= rx;
    int rightPosx= rx+width;
   // cout<<"topPosy= "<<topPosy<<" botPosy= "<<botPosy<<" leftPosx= "<<leftPosx<<" rightPosx= "<<rightPosx<<endl;
    //what dimensions to check inside?
    
    
    //check x is good
    if ((posx > leftPosx) && (posx < rightPosx) ) {
        if ((posy > topPosy) && (posy < botPosy) ) {
            inside=1;
        } // inside y?
        
    }//inside? x
   
    
    return inside;
}





void ofApp::erasecircles() {
//
//
//   ERASE CIRCLES
//
//
//   CHANGE COLOR OF "RESTART" BOX TO HIGHLIGHT ITS ACTIVE
//
//
//
//
//
//
    
    
    
    
    for (int i=0; i <1; i++) {
        rr=255;
        gg=55;
        bb=0;
        counterErase++;
        if ( counterErase%100000 && separateCircles.circles.size()>0) separateCircles.circles.erase(  separateCircles.circles.begin() + i );
    }
    
    
    if (separateCircles.circles.size()==0) {
        cout<<"RSTARTING*******************************"<<endl;
        myDelay = ofGetElapsedTimeMillis() +2000;
        programOnoff=1;
    }//no circles left retart
}


//--------------------------------------------------------------
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
    
    
    // if messages greater than message buffer then delete them
    if (messageBuffer.size()>maxBufferSize) messageBuffer.pop_back();
   
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
         cout<<" DATA FROM OSC"<<endl;
        //
        // m.setAddress("/infrared/position");
        //m.addIntArg(x);
        // m.addIntArg(y);
        
        // check for wand has moved message
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
            cout<<" DATA FROM OSC"<<endl;
             cout<<" programOnoff=====    "<<programOnoff<<endl;
            cout<<"markerX= "<<markerX<<"   markerY= "<<markerY<<endl;
            cout<<"randomMaxBubbles ====="<<randomMaxBubbles <<endl;
            cout<<"separateCircles.circles.size()"<<separateCircles.circles.size() <<endl;
            
            
                //  cout<<"ofGetElapsedTimeMillis()= "<<ofGetElapsedTimeMillis()<<endl;
                //  cout<<"separateCircles.newGameTime= "<<separateCircles.newGameTime <<endl;
                //   cout<<"separateCircles.bubblesKilled= "<<separateCircles.bubblesKilled<<endl;
                //     cout<<"separateCircles.circles.size()= "<<separateCircles.circles.size()<<endl;
                //if (separateCircles.bubblesKilled < 3) {
                //control the number of bubbles
            if (programOnoff==1) {
                
                if (ofGetElapsedTimeMillis() > myDelay) {
                    
                    
                    if (separateCircles.circles.size()>40) {
                        // can push circles
                        pushForceOnoff=1;
                        
                        // cant add more circles
                        cout<<"pushForceOnoff*******************************"<<endl;
                        cout<<"pushForceOnoff="<<pushForceOnoff<<endl;
                        
                    }//push force activate
                
                // LIMIT NUMBER OF BUBBLES WITH  "randomMaxBubbles"
                if (separateCircles.circles.size() < randomMaxBubbles ) {
                   
                    // create circles inside image display
                    if (( markerX > 10 && markerX < 1270) && ( markerY > 10 && markerY < 780)) {
                        // cant push circles
                        pushForceOnoff=0;
                        // add a counmter to slow down creation of circles with the wand
                        
                        counterSlowdown++;
                       

  if (counterSlowdown%50==0)separateCircles.addone(markerX,markerY);
                    } // within screen create
                    
                } else {
                    
                    programOnoff=0;
                }//end if randomMaxBubbles"
                    
                    
                } //mydelay
                
                
                
            }//  programOnoff=0;
                
          
            
            
           
            
            
        } else {
            // unrecognized message: display on the bottom of the screen
            messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
        }
        
    } // while loop
    
}// osc recieved





