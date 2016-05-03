#include "ofApp.h"
#include <string>

// initialize the objects we will use
ofFbo fbo;
ofVideoPlayer mov0;
ofSerial serial;
ofImage img0;
ofImage img1;

string staging;  // buffer for strings from serial port

int w, h, X, Y, Z, midX, midY, avX, avX2, avatarY, size;

void testApp::setup(){
	
  // setup globals
  w = ofGetWidth();
  h = ofGetHeight();
  midX = ofGetWidth()/2;
  midY = ofGetHeight()/2;
  avX = midX;
		avX2 = midX;
  avatarY = midY;
	
		// setup font
		windy.load("OratorStd-Slanted.otf", 100);
	
  // setup image
		img0.load("lashL.png");
		img1.load("lashR.png");
	
  // set up the serial device
  serial.setup("/dev/cu.usbmodem1421", 9600); // load a specific serial port when not on RPi
  serial.setup(0, 9600); //open device 0 @ 9600 baud

  // setup movie
  mov0.load("water.mp4");
  mov0.setLoopState(OF_LOOP_NORMAL);
  mov0.play();
	
  backgroundMusic.loadSound("lion.mp3");
  backgroundMusic.setLoop(true);
  backgroundMusic.play();
  
  // limit drawn frames per sec
  ofSetFrameRate( 60 );
}

// This takes a delimiter and a string.  It will look for the delimiter, go one character beyond and convert the first 
// number it sees in the string to an integer.  This will be used for the strings coming from the arduino"s gyro.
int parseInt (string del, string str) {

  std::size_t found = str.find(del);
  int rv = atoi(str.c_str() + found + del.length());
  return (rv);
}

// update all the variables and data in the program!
void testApp::update(){

  mov0.update();

#if 0
  int ttl = 100; // read x chars MAX..  if more available... throw em out!
  char ch;
  while ((ch=serial.readByte())>0 && ttl-->0 && ch != '\n') {
    staging += ch;
  }

  if (ch == '\n') {
    // parse gyro input, correspond strings to variable
    X = parseInt("X:", staging); // relative value of x 
    Y = parseInt("Y:", staging); // relative value of y 
    Z = parseInt("Z:", staging); // relative value of z
    char buffer[300];
    sprintf(buffer, "%d %d %d", X, Y, Z);
    avatarX += X;
    avatarY += Y + 3;
    avatarX = ofClamp(avatarX, 0, ofGetWidth());
    avatarY = ofClamp(avatarY, 0, ofGetHeight());
    staging = "";
  }
#endif
}

void testApp::mouseMoved(int x, int y){
    avX = x;
				avX2 = x;
    avatarY = y;
}

void eyes() {
	ofColor blu;
	blu.r=0;
	blu.g=0;
	blu.b=100;

	ofColor red;
	red.r=255;
	red.g=85;
	red.b=40;
	
	// dialate pupils
	if (size < 70){
		size++;
	} else if (size >= 70) {
		size--;
	}
	
	ofCircle (avX - 300, 300, size);
 ofCircle (avX2 + 350, 300, size);
	ofSetColor(blu);
	
	ofCircle (avX - 300, 300, 30);
	ofCircle (avX2 + 350, 300, 30);
	ofSetColor(red);
	
	// collision, keep pupils inside eyes
	if (avX > 500) {
		avX = avX - 300;
	}
	
	if (avX2 > 500) {
		avX2 = avX2 - 350;
	}
}

void testApp::draw(){
  
		// background
		ofColor out = ofColor(60,0,0);
  ofColor in = ofColor(0,0,0);
  ofBackgroundGradient(in, out, OF_GRADIENT_CIRCULAR);

		mov0.draw(50, 150);
		img0.draw(-150, 100);
		mov0.draw(670, 150);
		img1.draw(650, 100);
	
		eyes();
	
		// text
		windy.drawString("5&*^%%*#)874920", 0, 120);
	
}

