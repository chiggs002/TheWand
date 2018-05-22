#pragma once

#include "ofMain.h"
#include "Circle.h"
#include "RepeatExplosion.h"
#include "ofxMaxim.h"


class SeparateCircles : public ofBaseApp{
    
public:
    SeparateCircles();
    void setup(int mX,int mY,float velMax,int maxCircles,int bursttime);
    void addone(int mX,int mY,int busttime);
    void update();
    void draw(int mX,int mY);
    void mouseMoved(int x, int y );
    void circleboundaries();
    void circleinside(int x, int y);
    void audioOut ( float * output, int bufferSize, int nChannels);

    
    
//    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
//
    
    ofTrueTypeFont myfontBold;
    ofTrueTypeFont myfontReg;
     vector <Circle> circles;
    vector <ofVec2f> scoressofar;
     vector <ofVec2f> holder;
    int  bubblesKilled;
    int  bubblesEscaped;
    int  newGameTime;
    int timeLeft;
     int addTen;
    int loopover10;
    int loopover;
    
   // Boolean newGame;
    int newGame;
    int numberGames;
    int myflagEmpty;
    int startFrom;
   // int holder[10] = {0,0,0,0,0,0,0,0,0,0};
    // SET UP EXPLOSIONS
    RepeatExplosion repeatExplosions;
    
    
    //// ALL AUDIO
    
    
    
    
    
    
    
    ////////////////////
    int bufferSize; /* buffer size */
    int sampleRate;
    int timePassed;
    int delayTime;
    
    
    // maxiOsc osc1,osc2;
    
    float freq, amp;
    float globalT;
    
    float modIndex;
    float modfreq;
    float finalFreq;
    float p;
    double frequency, currentSample, currentVolume;
    double outputs[2];
    
    
    //  THE WAY OF TRIGERRING THE MELODY AND THE MELODY IS MINE.
    //  I MADE THE FREQUENCIES USING MAXMSP AND MIDI TO FREQ. PATCH
    //  I CHOSE ODE TO JOY AND PLAYED ON A KEYBOARD. CONTAINS A FEW ERRORS.
    //  TONE[58]== ODE TO JOY MELODY
    int tone [58] = { 184,184,195,220,220,195,184,164,146,146,164,184,184,164,164,184,184,195,220,220,195,184,164,146,146,164,184,164,146,146,164,164,184,146,164,184,195,184,164,146,164,123,110,184,184,195,220,220,195,184,164,146,146,164,186,164,146,146};
    
    int counterK;
    int clockz;
    maxiOsc osc1;
    maxiOsc osc2;
    maxiOsc osc3;
    maxiOsc osc4;
    maxiEnv env;
    maxiMix mix;

};
