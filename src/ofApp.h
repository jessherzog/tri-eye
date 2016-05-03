#pragma once
#include "ofMain.h"

extern int NPPAlive[];
extern const int numNPPoints;
extern void NPPUpdate (int idx);
extern void NPPDraw (int idx);
extern bool NPPCollisionDetection (int idx);

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void mouseMoved(int x, int y);
        ofSoundPlayer backgroundMusic;
    
    ofTrueTypeFont windy;
};
