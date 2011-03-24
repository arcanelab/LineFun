/*
 *  testApp.cpp
 *  LineFun
 *
 *  Created by Zolt‡n Majoros on 11 / 3 / 16.
 *  Copyright 2011 Zolt‡n Majoros. All rights reserved.
 *
 */

#include "testApp.h"

//--------------------------------------------------------------
// this routine is from stackoverflow.com by http://stackoverflow.com/users/225238/infinityloop
// generates a random floating point number between [0-1]
float rnd(void)
{	//Generate a random number in the range [0.5f, 1.0f).
	unsigned int ret = 0x3F000000 | (0x7FFFFF & ((rand() << 8) ^ rand()));
	unsigned short coinFlips;
	
	//If the coin is tails, return the number, otherwise
	//divide the random number by two by decrementing the
	//exponent and keep going. The exponent starts at 63.
	//Each loop represents 15 random bits, a.k.a. 'coin flips'.
#define RND_INNER_LOOP() \
if( coinFlips & 1 ) break; \
coinFlips >>= 1; \
ret -= 0x800000
	for(;;){
		coinFlips = rand();
		RND_INNER_LOOP(); RND_INNER_LOOP(); RND_INNER_LOOP();
		//At this point, the exponent is 60, 45, 30, 15, or 0.
		//If the exponent is 0, then the number equals 0.0f.
		if( ! (ret & 0x3F800000) ) return 0.0f;
		RND_INNER_LOOP(); RND_INNER_LOOP(); RND_INNER_LOOP();
		RND_INNER_LOOP(); RND_INNER_LOOP(); RND_INNER_LOOP();
		RND_INNER_LOOP(); RND_INNER_LOOP(); RND_INNER_LOOP();
		RND_INNER_LOOP(); RND_INNER_LOOP(); RND_INNER_LOOP();
	}
	return *((float *)(&ret));
}


//--------------------------------------------------------------
void testApp::setup()
{
	bFullscreen = FALSE;
	ofSetFrameRate(60);
	ofSetVerticalSync(TRUE);
	ofEnableSmoothing();
	ofSetBackgroundAuto(FALSE);
	
	float minSpeed = 0.0f;
	int maxSpeed = 1.0f;
	
	line.x1 = arc4random() % ofGetWidth();
	line.y1 = arc4random() % ofGetHeight();
	line.x2 = arc4random() % ofGetWidth();
	line.y2 = arc4random() % ofGetHeight();
	line.sx1 = rnd() * maxSpeed + minSpeed;
	line.sy1 = rnd() * maxSpeed + minSpeed;
	line.sx2 = rnd() * maxSpeed + minSpeed;
	line.sy2 = rnd() * maxSpeed + minSpeed;
	
	rr = arc4random()%3+3;
	rg = arc4random()%3+3;
	rb = arc4random()%3+3;
	
	ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::update()
{
	int screenWidth = ofGetWidth();
	int screenHeight = ofGetHeight();
	
	float t = ofGetElapsedTimef();
	
	// move points around. the linear motion is spiced up with some sinusoid moves.
	line.x1 += line.sx1 + sin(t) * cos(t/2);
	line.y1 += line.sy1 + sin(t/2) * sin(t/2 + 2);
	line.x2 += line.sx2 + cos(t/2) * sin(t/3 + 1);
	line.y2 += line.sy2 + cos(t) * sin(t/3);
	
	// check border-collision. if border is crossed, limit movement and negate move direction
	if(line.x1 < 0)
	{
		line.x1 = 0;
		line.sx1 = -line.sx1;
	}
	if(line.x1 >= screenWidth)
	{
		line.x1 = screenWidth - 1;
		line.sx1 = -line.sx1;
	}
	if(line.y1 < 0)
	{
		line.y1 = 0;
		line.sy1 = -line.sy1;
	}
	if(line.y1 >= screenHeight)
	{
		line.y1 = screenHeight - 1;
		line.sy1 = -line.sy1;
	}
	if(line.x2 < 0)
	{
		line.x2 = 0;
		line.sx2 = -line.sx2;
	}
	if(line.x2 >= screenWidth)
	{
		line.x2 = screenWidth - 1;
		line.sx2 = -line.sx2;
	}
	if(line.y2 < 0)
	{
		line.y2 = 0;
		line.sy2 = -line.sy2;
	}
	if(line.y2 >= screenHeight)
	{
		line.y2 = screenHeight - 1;
		line.sy2 = -line.sy2;
	}
	
	// generate smooth color change
	line.r = (int)(sin(t/rr+rb) * 255);
	line.g = (int)(sin(t/rg-rr) * 255);
	line.b = (int)(cos(t/rb+rg) * 255);
//	line.r = (int)(sin(t/3) * 255);
//	line.g = (int)(sin(t/4) * 255);
//	line.b = (int)(cos(t/5) * 255);
}

//--------------------------------------------------------------
void testApp::draw()
{
	static float fpsSum = 0;	// needed for calculation of average fps
	static int counter = 0;		// detto
	static int lastT = 0;		// used to detect seconds passing by
	
	ofSetColor(line.r, line.g, line.b, 128); // set the color of the line (last param is alpha)
	ofLine(line.x1, line.y1, line.x2, line.y2); // draw the line
	
	// calculate FPS. instead of updating the FPS in every frame, we calculate the average for a second 
	float t = ofGetElapsedTimef(); // get elapsed time in seconds (int a floating point number)
	int r = t - (int)t/10; // r will contain an integer time value holding the actual 'seconds' value
	
	if(lastT != r) // lastT holds the previous seconds value. check if it changed
	{ // it did, it means we have a second passed
		float avgFps = fpsSum / (float)counter;	// calculate the avg. FPS value
		std::string str; // convert into string
		str += "fps: " + ofToString(avgFps, 2) + " - press 'f' for fullscreen, 'c' for clearing screen, 's' for saving a screenshot into ./data/";
		ofSetWindowTitle(str); // and set window title to the previously specified text
		
		counter = 0; // reset helper variables
		fpsSum = 0.0f;
		lastT = r;
	}
	else { // we're still in the same second, just update our counters
		fpsSum += ofGetFrameRate();
		counter++;
	}
}
/*
//--------------------------------------------------------------
 void testApp::keyReleased(int key)

}
*/
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	if(key == 'f') // toggle fullscreen
	{
		bFullscreen = !bFullscreen;
 
		if(!bFullscreen)
		{
			ofSetWindowShape(1024,640);
			ofSetFullscreen(false);
			// figure out how to put the window in the center:
			int screenW = ofGetScreenWidth();
			int screenH = ofGetScreenHeight();
			ofSetWindowPosition(screenW/2-1024/2, screenH/2-640/2);
		}
		else if(bFullscreen == 1)
		{
			ofSetFullscreen(true);
		}
	}
	
	if(key == 's') // save image
		ofSaveFrame();
	
	if(key == 'c') // clear screen
	{
		ofBackground(0, 0, 0);
		ofBackground(0, 0, 0); // no mistake, one call might not _always_ clear the screen. (maybe due to double-buffering?)
	}
 
}
/*
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
*/
