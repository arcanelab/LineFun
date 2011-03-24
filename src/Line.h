/*
 *  Line.h
 *  LineFun
 *
 *  Created by Zoltán Majoros on 11 / 3 / 16.
 *  Copyright 2011 Zoltán Majoros. All rights reserved.
 *
 */

#ifndef __LINE_H__
#define __LINE_H__

class LineClass
{
public:
	float x1, y1, x2, y2;		// P1(x1,y1) - P2(x2,y2) = two point of the line
	float sx1, sy1, sx2, sy2;	// speed values for each coordinates
	float r, g, b;				// the RGB color component values for the line
};

#endif