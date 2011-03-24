/*
 *  testApp.h
 *  LineFun
 *
 *  Created by Zolt‡n Majoros on 11 / 3 / 16.
 *  Copyright 2011 Zolt‡n Majoros. All rights reserved.
 *
 */

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Line.h"

class testApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
//	void keyReleased(int key);
/*	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
*/	
	LineClass line;
	int bFullscreen;
	int rr, rg, rb; // random coefficients for the color components
};

#endif
