//
//  This code creates ALL THE CIRCLES EMITTED FROM THE WAND
//
//  Reqires the file:
//
//  "IFRARED TRACKING 03 osc" to recieve position inputs
//  from a infrared sensor. Data is recieevd via OSC
//
//
//  ALL CIRCLES ARE EMITTED WITH NO FORCE BUT ALL HAVE A INITAL RANOM VELOCITY AND RADIUS
//
//
//
//  SeperateCircles.cpp
//  Circlepacking
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

#include "SeparateCircles.h"
#include "Circle.h"



SeparateCircles::SeparateCircles() {
//
//
//
//
//
// SET UP ALL THE GAME TEXT INFORMATION AND INITIAL GAME VARIBALES
//
//
//
//
//

    
    
    // INITIAL NUMBER OF GAMES
     cout<<"HEADER CALEED HEADER CALLED"<<newGame<<endl;
     numberGames=0;
    
    
    // setup the variables for a new game to begin
    bubblesKilled =0;
    bubblesEscaped =0;
    myflagEmpty=1;
    ofVec2f b;
    b.set(0,0);
    //scoressofar.push_back(b);
    
    // EVRY NEW GAME HAS A COUNT DOWN BEFORE IT BEGINS
    newGame=1;
    newGameTime = ofGetElapsedTimeMillis() + 3000;
    addTen=0;
    loopover10=1;
    loopover=1;
    holder.resize(10);
     clockz=1;
    counterK=0;
    
    cout<<"STARTnewGame= "<<newGame<<endl;
    
    
    // setup display text KEEPS TRACK OF GAME SCORES AND NUMBER OF BUBBLES ON SCREEN
    
    
   // myfontBold.load("DIN-Bold.otf",12);
   // myfontReg.load("DIN-Regular.otf",12);
    myfontBold.load("DIN-Bold.otf",17);
    myfontReg.load("DIN-Regular.otf",17);
    //,int bursttime
    // circles.resize(maxCircles);
    //  for(int i=0; i<circles.size(); i++){
    
    //// AUDIO SETUP  BETWEEN A NEW SOUND
    //audio parameters
    timePassed=0;
    delayTime=200;
    
    
    //get envelope object FOR THE AUDIO
    env.setAttack(200);
    env.setDecay(1);
    env.setSustain(1);
    env.setRelease(3000);
    
    // SET UP A BUFFER AND SAMPLE RATE
    sampleRate     = 48000; /* Sampling Rate */
    bufferSize    = 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    // initial SOUND  FREQUENCY values
    frequency =440;
    freq = 348;
    amp = 1;

}





void  SeparateCircles:: setup(int mX,int mY,float velMax,int maxCircles,int bursttime) {
//
//
//   GENERATE RADOM WOBBLY CIRCLES WITH RANDOM KINEMATICS AND RADIUS
//
//
//
//
//
//
//
//
    
 
   
  
    
    
   
    // setup default circles
        for(int i=0; i<maxCircles; i++){
   
            float myRadius=ofRandom(2,20);
            Circle b;
            b.setup(mX,mY,myRadius,ofRandom(0,velMax),int(ofRandom(bursttime,bursttime+5000)),ofRandom(255),ofRandom(255),ofRandom(255));
            circles.push_back(b);
             
        } //generate maxCircles
        
    
    
    
}//setup







void  SeparateCircles:: addone(int mX,int mY,int busttime) {//
//
//
//
//  add a single circle
//
//  takes inputof current emanate points and time in which
//  bubble cannot be burst before ofRandom(1000,5000)
//
//
//
//
//
//
//
    
    // CHOOSE RANDOM SIZE
     float myRadius=ofRandom(15,20);
   // cout<<"myRadius= "<<myRadius<<endl;
    // push another circle class.
    // inputs:  position: mX,mY ....radius..myRadius...max velocity ofRandom(0.1,1.3) and burst bubble time ofRandom(1000,5000)
    // speed var 0.1,1.3
    
    // RANDOMIZE RADIUS BURST TIMEAND COLORS IF USED
    Circle e;
    e.setup(mX,mY,myRadius,ofRandom(0.1,0.9),int(ofRandom(1000,5000)),ofRandom(255),ofRandom(255),ofRandom(255));
    circles.push_back(e);
   
}



void  SeparateCircles::update() {
//
//
//
//  UPDATE BUBBLE KINEMATICS (VELOCITY AND POSITION)
//
//
//
//
//
//
//
//
//
//
    
    
    //UPDATE EXPLOSIONS
    repeatExplosions.update();
    
    for(int i=0; i<circles.size(); i++){
        circles[i].update();
    }
}








//// DRAW  THE BUBBLES


void  SeparateCircles:: draw(int mX,int mY) {
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
//
    
    // DRAW ALL EXPLOSOIONS IF THEY HAVE BEEN TRIGGERED?
     repeatExplosions.draw();
    
    // RESET THE GAME NO BUBBLES LEFT
    if (circles.size()==0 ) {
         myflagEmpty=1;
        // add a single circle into the array so the counter size is non zero. and we dont keep reseting the game
        Circle d;
        d.setup(mX,mY,ofRandom(8,12),ofRandom(0.1,1.3),int(ofRandom(1000,5000)),ofRandom(255),ofRandom(255),ofRandom(255));
        circles.push_back(d);
        
    }// ADD 1 CIRCLE RESeTS GAME
    
    
    
    
    // if no bubbles left then reset scores.
    if (myflagEmpty==1 ) {
        myflagEmpty=0;
        
        cout<<"circles.size()=======>"<<circles.size()<<endl;
        
        cout<<"---------------"<<endl;
        cout<<"NOMORE CIRCLES"<<endl;
        cout<<"---------------"<<endl;
       
        cout<<"numberGames="<<numberGames<<endl;
        
        cout<<"SCORE ARRAY SIZE "<<scoressofar.size()<<endl;
        
        //RECORD THE SCORE into a array keep pushing scores back
        ofVec2f c;
        c.set(bubblesKilled,bubblesEscaped);
        scoressofar.push_back(c);
        
        //LOOP OVER LAST 10 scores
        //only shows last ten scores
        loopover10++;
       
            
        
        
       
        
        // game counter
        // How many games have we played?
        numberGames++;
        
        
        // new game will begin after current game finishes 10 secs later
        newGameTime = ofGetElapsedTimeMillis() + 10000;
        
        //SET VARIABLE TO NEW GAME: triggers a new game to commence
        newGame= 1;
        cout<<"circles.size()AFTER AFTER AFTER AFTER=======>"<<circles.size()<<endl;
     
    } // IF MYFLAG==1  SET NEW DELAY TIME UNTIL NEXT GAME
    
    
    
    
    
  
    
    
     //DRAW ALL CIRCLES/BUBBLES ONTO SCREEN
    // After new game time has finished for 10 seconds
    //
    // If new game time has finsihed countdown to new game:
    // countdown to new game and display all scores
    //
    // 10 seconds till new game commences: show all scores so far (last 10)
    //
    //
    if ( ofGetElapsedTimeMillis() > newGameTime  ) {
            // WE HAVE COMMENCED A NEWGAME AS COUNTDOWN HAS FINISHED
        
        
            //add the display type to screen GAME SCORE
            ofPushStyle();
            ofSetColor(0,0,0);
            myfontBold.load("DIN-Bold.otf",20);
            myfontReg.load("DIN-Regular.otf",20);
            string myheader = "No.of bubbles left   " + ofToString(circles.size());
            string myscore  = "My score   " + ofToString(bubblesKilled);
            string computerscore  = "Computer's score   " + ofToString(bubblesEscaped);
            
            //ofDrawBitmapString(myheader, 30, 30);
            myfontBold.drawString(myheader, 130, 60);
            myfontBold.drawString(myscore, 450, 60);
            myfontBold.drawString(computerscore , 670, 60);
            ofPopStyle();
            
        
            // DRAW THE NEW BUBBLES PRODUCED BY THE WAND
        
            for(int i=0; i<circles.size(); i++){
               circles[i].draw();
            }
       
            
            // IF I have successfully selected a CIRCLE to DELETE  BY USING THE WAND then delete IT
            circleinside(mX, mY);
            
            
            //delete any circles outside of boundaries of the screen
            circleboundaries();
            
            
    }// newgmetime over
    
  
    
   
    
    // Have we started a new game?
    // in between the 10 sceonds before the new game begins display the "red" type instructions
    //
    //
    // DISPLAY THE NEW GAME STATISTICS  AND INSTRUCTIONS  ALLIN RED TYPE
    //
    //
    //
    if (newGame) {
        
        if ( ofGetElapsedTimeMillis() < newGameTime  ) {
            // tell the spectactor how much time before new game starts
            timeLeft= (newGameTime-ofGetElapsedTimeMillis())/1000.0;
            ofSetColor(255,0,0);
            string newgame  = "NEW GAME STARTS  " + ofToString(timeLeft) + " secs";
            string wavewand  = "Wave the wand around to create bubbles. ";
            string nobubbles   = "You have created  " +ofToString(circles.size()) + " bubbles.";
          
            myfontBold.drawString(wavewand , 100, 30);
            //myfontBold.drawString(nobubbles , 100, 60);
              myfontBold.drawString(newgame , 100, 90);
            
            string bubbleskilled  = "Last 10 scores:   killed V Escaped";
            myfontBold.drawString(bubbleskilled , 780, 90);
            
            //cout<<"scoressofar.size="<<scoressofar.size()<<endl;
           
            
            // TRY AND KEEP THE LAST 10 SCORES ON SCREEN : THEY ARE ALL STORED IN AN ARRAY
           
            if (loopover10%10==0) {
               
                addTen++;
               
                cout<<"LOOPED 10 TIMES"<<"  addTen= "<<addTen<<endl;

            }
            
            // EVERY 10  GAMES CHNAGE THE ACCESS SYSEM TO THE SCORES
            // SO THE LAST 10 SCORES ARE ONLY SHOWN ON SCREEN
            if (addTen==0) {
                startFrom=1;
                loopover = scoressofar.size();
            } else if (addTen==1) {
                startFrom=numberGames%10;
                loopover = numberGames;
            } else if (addTen >=2) {
                startFrom=numberGames%10 + (addTen-1)*10;
                loopover = numberGames;
            }
            
           
            // DISPLAY SCORES UPTO LAST TEN THAT HAVE BEEN STORED IN A ARRAY: scoressofar[i]
            for(int i=startFrom; i<loopover; i++){
            
             //    cout<<"scoressofar="<<scoressofar[i].x<<" v  "<<scoressofar[i].y<<endl;
                string scores = ofToString(scoressofar[i].x) + " V " +ofToString(scoressofar[i].y);
                myfontBold.drawString(scores , 1035, 120+(25*i));
                
            } //keep scores
            
            
            
          //  cout<<"WAITING FOR RESET "<<endl;
        }else {
        // WE HAVE STARTED A NEW GAME RESET TRACKERS ON GAME POINTS
            
        // after new game begins set new game to zero.
           newGame = 0;
            
        
        // reset game variables.
            bubblesKilled =0;
            bubblesEscaped=0;
            
        }
        
        
    }//if new game true
    
    
    //turn off envelope aftertime has expired
//    if (ofGetElapsedTimeMillis() > timePassed - (delayTime/2.0)) {
//        env.trigger=0;
//    }
    
    // AUDIO CLOCK SWITCHES ON AND OFF A ADSR SWITCH
    // USES A MODULO FOR TIMING
    clockz++;
    cout<<"ZOUT=="<<clockz<<endl;
    
    // MY MELODY SIZE IS 58 TONES LONG . REPEAT THE MELODY AGAIN AND AGAIN
    counterK=counterK%59;
    cout<<"counterK =="<<counterK<<endl;
    
    // MY BEAT CLOCK
    if (clockz%25==0) {
        // set adslr trigger to off
        env.trigger=0;
        
    }//my clock trigger
    
}//end draw











void SeparateCircles:: mouseMoved(int x, int y ) {
// NOT USED
    
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
            bubblesEscaped++;
           // cout <<"circle element deleted current size = " << circles.size() <<endl;
        }
        if (circles[i].position.y <0 || circles[i].position.y > ofGetHeight()  ) {
            circles.erase( circles.begin() + i );
           // cout <<"circle element deleted current size = " << circles.size() <<endl;
            bubblesEscaped++;
        }
    }
} //circleboundaries


void SeparateCircles::circleinside(int x, int y) {
//
// AM I INSIDE ANY CIRCLE USING X,Y AS INPUTS ?
//
// IF YES: DELETE THEM
// IF NO:  DO NOTHING
//
// USE THE POSITION AND RADIUS OF THE CIRCLE TO ANWSER THIS QUESTION
//
//
//
    
    //cout <<"circles ARRAY  size BEFORW = " << circles.size() <<endl;
    
    // LOOP AROUND EVERY  CIRCLE
    for(int i=0; i<circles.size(); i++){
        
        //cout  <<"............................."<<endl;
        // cout  <<"............................."<<endl;
        // cout  <<"............................."<<endl;
        //cout  <<"circles.size() = ="<<circles.size()<<endl;
        // cout  <<"mouse x= "<<x<<"mouse y= "<<y<<endl;
        //cout  <<"position.x= "<<circles[i].position.x<<"position.y= "<<circles[i].position.y<<endl;
        float checkx= abs(circles[i].position.x-x);
        // cout <<"checkx = " <<checkx<<endl;
        float checky= abs(circles[i].position.y-y);
        
        // cout <<"checkx= " <<checky<<endl;
        
        //CHECK IF WAND IS OVER THE BUBBLES
        if (checkx < circles[i].radius && checky < circles[i].radius  ) {
            //circles.erase(  circles.begin() + i )

            //if we can burst the bubbles yet?
            if( circles[i].canBurst) {
                
                // ADD AUDIO TO SCENARIO
                // audio out
                // playsound out
                
                // set ADSR trigger to on and off
                
                // change frequency of the output
                // tone[58] = ode to joy beethoven
                
                frequency = tone[counterK]*2;
                env.setRelease(30);
                // set adslr trigger to on
                env.trigger=1;
                // CHANGE NOTE TO PLAY
                counterK++;
                
                
                
//                // my clock for beats
//                if (clockz%25==0) {
//
//                    // set adslr trigger to off
//                    env.trigger=0;
//                    counterK++;
//                    counterK=counterK%59;
//                    cout<<"counterK =="<<counterK<<endl;
//                }//my clock trigger
                
                
                
//
//                if ( ofGetElapsedTimeMillis() > timePassed) {
//                    frequency = ofRandom(120,670);
//                    env.setRelease(ofRandom(50,1000));
//                    env.trigger=1;
//                    timePassed= ofGetElapsedTimeMillis()+ delayTime;
//                } else  if (ofGetElapsedTimeMillis() > timePassed - (delayTime/2.0)) {
//                    env.trigger=0;
//                }
                
                
                
                
                // draw the red zone marker when I have deleted a bubble
                // keeps on flashing up when a bubble is deleted
                ofSetColor(255, 0, 0);
                ofDrawCircle(circles[i].position, 100);
                
                // SET UP EXPLOSIONS by getting current wand position
                // float mX = ofGetMouseX();
                //  float mY = ofGetMouseY();
                float mX = circles[i].position.x;
                float mY = circles[i].position.y;
                cout  <<"PRESSED MOUSE POSITION "<<"mX = "<<mX<<"mY = "<<mY<<endl;
                
               // repeatExplosions.push_back(b);
                // create 1 set of explosions 
                repeatExplosions.setup(mX,mY);
                
                
               // add one to counter bubbblekilled
               bubblesKilled++;
                
                
               //cout <<"circles[i].burstTime; = " <<circles[i].burstTime<<endl;
               // ERASE CIRCLE THAT HAS BEEN DELETED
               circles.erase(  circles.begin() + i );
                
           
            
            }// if time has passed
            
            
           // cout  <<"............................."<<endl;
          //  cout  <<"............................."<<endl;
           // cout  <<"............................."<<endl;
            // cout <<"INSIDE CIRCLE " <<endl;
           // cout  <<"circles.size() = ="<<circles.size()<<endl;
            // cout <<"checky= " <<checky<<endl;
            //cout <<"checkx = " <<checkx<<endl;
            
        
        } //is wand over bubbles?
        
    } //LOOP AROUND EVERY  CIRCLE
    
} //circleinside











// --------------------------AUDIO OUT----------------------------------------

void SeparateCircles::audioOut(float * output, int bufferSize, int nChannels) {
//  THE BASIC AUDIO FUNCTION IS FROM CLASS WORK ON USING MAXIM ADDON
//  THE BASIC SETUP OF A ADSLR IS FROM A MAXIM EXAMPLE
//
//  THE WAY OF TRIGERRING THE MELODY AND THE MELODY IS MINE.
//  I MADE THE FREQUENCIES USING MAXMSP AND MIDI TO FREQ. PATCH
//  I CHOSE "ODE TO JOY" AND PLAYED ON A KEYBOARD. CONTAINS A FEW ERRORS.
//
//
//
//
//
//
//
    for (int i = 0; i < bufferSize; i++){
        
      
        
        
        double wave;
        //modfreq= osc2.sinewave(1);
        float p= osc3.phasor(0.5,1,100);
        modfreq= osc2.sinewave(p);
        //modfreq= (osc2.square(p)+1)/2;
        wave = osc1.sinewave(freq) * modfreq;
        wave = wave * amp;
        
        
        //wave = osc1.sinewave(440) * osc2.sinewave(osc3.phasor(0.2, 1, 200));
        
        //        //doing it manually
        //        //wave = sin(globalT);
        //        //globalT+=1./40.;
        //
        ////        output[i*nChannels    ]= wave;
        ////        output[i*nChannels + 1]= wave;
        ////
        
        // SETUP ENVELOPE FOR A ADSLR TIGGER IS EITHER ON OR OFF  env.trigger=1/0
        currentSample= env.adsr(osc4.sinewave(frequency), env.trigger);
        
       
        // OUTPUT TO STEREO 0.5= EQUAL LEFT/RIGHT SPEAKER
        mix.stereo(currentSample, outputs, 0.5);
        
        output[i*nChannels    ]= outputs[0];
        output[i*nChannels + 1]= outputs[1];
    }
    
}//AUDIOOUT








