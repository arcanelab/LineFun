/*
 *  main.cpp
 *  LineFun
 *
 *  Created by Zolt‡n Majoros on 11 / 3 / 16.
 *  Copyright 2011 Zolt‡n Majoros. All rights reserved.
 *
 */
#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main()
{
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,640 , OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new testApp());
}
