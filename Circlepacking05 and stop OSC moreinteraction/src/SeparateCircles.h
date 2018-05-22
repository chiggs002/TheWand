#pragma once

#include "ofMain.h"
#include "Circle.h"


class SeparateCircles : public ofBaseApp{
    
public:
    void setup(int mX,int mY,float velMax,int maxCircles);
    void addone(int mX,int mY);
    void update();
    void draw(int mX,int mY,int pushforceActive);
   
    void circleboundaries();
    void circleinside(int x, int y,int pushforceActive);
   
    
    //new CALCULATE SEPERATE FOCRCES ON CIRCLES
    ofVec2f calcSeparationForce(Circle c1, Circle c2 );
    void goThruSeparationForce(int i,vector <Circle> circ);
    float maxSpeed;// shiffman uses
    float maxForce;// shiffman uses
    void calcPushForce(int i);
    vector <ofVec2f> pushsepbetween;
    
    
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
    
    vector <Circle> circles;
    
     int  newGameTime;
};
