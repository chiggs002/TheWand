//
//  This code DETECTS THE AVERAGE POSITION OF THE INFRARED WAND BEING WAVED AROUND
//
//  important: Uses a ps3 eye camera as input
//
//  Reqires the file:
//
//  "CirclepGamebursting 11" to recieve position inputs OR "Circlepacking05 and stop OSC copy"
//
//  CirclepGamebursting 11: IS THE BUBBLE BURSTING GAME
//  Circlepacking05 and stop OSC copy: IS THE CIRCLE PACKINGGAME
//
//  from a infrared sensor. Data is recieevd via OSC
//
//
//   THIS IS TAKEN FROM A CLASS INSTRUCTIONAL PATCH
//
//
//   BAISC OPERATION:
//
//   THIS CODE CALULATES THE AVERAGE POSITION OF THE WAND THAT IS PAST ONTO THE GAMES TO USE:
//   It relies on pixe brightness to evalute this position
//
//   CirclepGamebursting 11 OSC: IS THE BUBBLE BURSTING GAME
//   Circlepacking05 and stop OSC copy: IS THE CIRCLE PACKINGGAME
//
//   A count down until a new game begins tells the user that a new game will commence in 'X' SECONDS (10 secs max)
//
//   PREVOUS SCORES ARE SHOWN IF THEY EXIST AND INSTRUCTIONS RE GIVEN ON BUBBLE CREATION ARE GIVEN.
//
//   ANY TIME AFTER THE GAME BEGINS AND THE WAND GOES OVER A BUBBLE IT IS DELETED AND THE SCORE IS UPDATE FOR THE USER
//
//   IF THE BUBBLES ESCAPES THE SCREEN DISPLAY A POINT IS GIVEN TO THE COMPUTER
//
//  SeperateCircles.cpp
//  Circlepacking
//
//
//
//  Created by CH on 17/03/2018.
//





// Finding the Brightest Pixel in an Image

#include "ofApp.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxOsc.h"



//---------------------
void ofApp::setup(){
//
//
//
//  SETUP OSC PORTS AND GRAB VIDEO (FROM SONY PLAYSTATION 3 EYE CAMERA )
//
//
//
//
//
    
    
    //setup setup port and address to send wand position
    sender.setup(HOST, PORT);
    
    
    
    //vidGrabber.setDeviceID(0);
    
    // Set the video grabber to the ofxPS3EyeGrabber.
    vidGrabber.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
   
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,480);
    rTarget = 255;
    gTarget = 182;
    bTarget = 193;
    threshold = 2.5;
      count = 0;
    closestColorX = 0;
    closestColorY = 0;
    sumclosestColorX = 0;
    sumclosestColorY = 0;
}
//---------------------
void ofApp::update(){
//
//
//
//  UPDATE AND GET IXELS VALUES OF IMAGE SEEN
//  RECORD THE PIXELS WITH THE BRIGHTEST VALUE AND AVERGE THEM OUT AS WELL
//
//
//
//
//
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){

        // these are used in the search for the location of the pixel
        // whose color is the closest to our target color.
       
        
        // setup a high value to reduce daylight interfernce
        int maxBrightness = 200;
        int w = vidGrabber.getWidth();
        int h = vidGrabber.getHeight();
      
     // loop over video image and find the brightest pixels
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
               
                
                // Extract the color components of the pixel at (x,y)
                // from myVideoGrabber (or some other image source)
                ofColor colorAtXY = vidGrabber.getPixels().getColor(x, y);
                int brightness = colorAtXY.getBrightness();
                
                //if color similar then add coordinates to sum
                // rests "maxBrightness" to new highest value
                if(brightness > maxBrightness){
                    // set up previous x and y values
                    lastclosestColorX= closestColorX;
                    lastclosestColorY= closestColorY;
                    
                   // cout<<"brightness= "<<brightness<<endl;
                    
                    closestColorX= x;
                    closestColorY= y;
                    
                    //cout<<"inside countcount="<<count<<endl;
                  //  closestColorX= lowPassAveraging(x,  count );
                   // closestColorY= lowPassAveraging(y,  count );
                
                    //cout<<"count="<<count<<endl;
                    //cout<<"SMOOTHclosestColorX = "<<closestColorX<<"SMOOTHclosestColorY = "<<closestColorY<<endl;
                    maxBrightness = brightness;
                
                    
                } //BRIGHTNESS
            }//ENDX
        } //ENDY
        cout<<"                   "<<endl;
        cout<<"                   "<<endl;
        cout<<"                   "<<endl;
        cout<<" inside brightness "<<endl;
        
        cout<<"NOclosestColorX = "<<closestColorX<<"    NOclosestColorY = "<<closestColorY<<endl;
        //        //calculate the average coordinate
        cout<<"                   "<<endl;
        cout<<"                   "<<endl;
        cout<<" outside brightness "<<endl;
        
        // SMOOTH OUT VALUES BY ADDING THEM TOGETHER THEN DIVIING BY A COUNTER
        sumclosestColorX+= closestColorX;
        
        sumclosestColorY+= closestColorY;
        count++;
        cout<<"count="<<count<<endl;
        cout<<"SUMX = "<< sumclosestColorX<<" SUMY = "<<sumclosestColorY<<endl;
       
        // SMOOTH OUT VALUES BY ADDING THEM TOGETHER THEN DIVIING BY A COUNTER
        closestColorX = sumclosestColorX / count;
        closestColorY = sumclosestColorY / count;
       
        cout<<"averageX = "<<closestColorX<<" averageY = "<<closestColorY<<endl;
        if (count % 5 ==0) {
            count=1;
            // RESET SMOOTH VALUES TO CURRENT BRIGHTNESS READING
            sumclosestColorX= closestColorX;
            sumclosestColorY= closestColorY;
            
        }
        

    } //END VIDEO
}//END UPDATE









//---------------------
void ofApp::draw(){
//
//
//
//  FLIP THE RECORED IMAGE TO GET THE CORRECT X AND Y READINGS
//
//
//
//
//
//
    
    
    // WHATS THE DIFF IN PREVOIUS READINGS?
    
    float lastdiffx= abs(lastclosestColorX-closestColorX);
    float lastdiffy= abs(lastclosestColorY-closestColorY);
    
    cout<<"lastdiffx= "<<lastdiffx<<"lastdiffy= "<<lastdiffy<<endl;
    ofPushMatrix();
  //ofTranslate(vidGrabber.getWidth(), 0);
  //  ofScale(-1, 1);
    
    // reverse image around
    ofTranslate(0, vidGrabber.getHeight());
    ofScale(1, -1);
    //vidGrabber.draw(0,0);
   //vidGrabber.draw(vidGrabber.getWidth(),0,-vidGrabber.getWidth(),vidGrabber.getHeight());
    
    // DRAW THE CURRENT CAMERA VIEW
    vidGrabber.draw(0, 0, vidGrabber.getWidth(), vidGrabber.getHeight());
    
    // WHATSTHE THRESHOLD SET TO? DISPLAY IT
    ofDrawBitmapString(threshold, 320, 20);
    //closestColorX= ofGetMouseX();
    //closestColorX= ofGetMouseY();
    
    
    // draw circle of average position detected
    if  (lastdiffx >= 0 && lastdiffy >= 0 ) {
        
        
    //only send data when its chnaged by more than 20 pixels
    // SEND OUT OSC DATA
    InfraredMoved(closestColorX, closestColorY);
    }
        
    ofDrawEllipse (closestColorX, closestColorY, 40,40);
    ofPopMatrix();
}












//---------------------
void ofApp::mousePressed(int x, int y, int button){
    // not used with the wand
    ofColor tempColor = vidGrabber.getPixels().getColor(x, y);
    rTarget = tempColor.r;
    gTarget = tempColor.g;
    bTarget = tempColor.b;
}
//-----------------------
void ofApp::keyPressed(int key){
    // not used with the wand
    if (key == OF_KEY_UP) threshold+=1;//UP ARROW
    else if (key==OF_KEY_DOWN) threshold-=1;//DOWN ARROW
}







//---------------------
float ofApp:: lowPassAveraging(double input, int points )
{
//
//
//   Smooth out infrared readings
//
//
//
//
//
    
    double sum = 0;
    for(int i = 0; i < points; ++i)
    {
        x[i] = input;
        sum += x[i];
         //cout<<" FINAL POINT ="<<i <<endl;
    }
   //sum += input;
  //  cout<<" FINAL sum ="<<sum <<endl;
   
    // x[0] = input;
    return sum/points;
}//average






//---------------------

void  ofApp:: InfraredMoved(int x, int y) {
//
//
//   SEND OUT OSC MESSAGES
//
//
//
//
//
//
//
    
    //remap y
    //1280,760
    // remap y as its upside down
    y = ofMap(y,0,480,480,0);
    
    // remap x and y to graphics SCREEN SIZE
    
    y = ofMap(y,0,480,0,760,true);
    x = ofMap(x,0,640,0,1280,true);
    y=ofClamp( y, 0, 760);
    x=ofClamp( x, 0, 1280);
   
    //#define HOST "localhost"
    //#define PORT 12345
    // DEINE MY OSC MESSAGE
        ofxOscMessage m;
        m.setAddress("/infrared/position");
        m.addIntArg(x);
        m.addIntArg(y);
        sender.sendMessage(m, false);
    }//end send





