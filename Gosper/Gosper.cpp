//
// Created by Jakob Wilter on 10/20/18.
//

/**
 * Gosper.cpp contains logic pertaining to the angles and points of the gosper shape in order to output
 * a graphed gosper curve onto a postscript file.
 *
 * Driver provided for by Professor Fukuda. Build code to compile for test driver.
 **/

#include "Gosper.h"

const int RIGHT = -60;
const int LEFT = 60;

//------------------------- Gosper Arrowhead ----------------------------
Gosper::Gosper(float initialX, float initialY, float initialAngle) : Turtle(initialX, initialY, initialAngle) {

}

//------------------------- leftCurve ----------------------------
//Turn -60.
//Draw a straight line.
//Turn +60.
//Draw a straight line.
//Draw a straight line.
//Turn +60.
//Turn +60.
//Draw a straight line.
//Turn +60.
//Draw a straight line.
//Turn -60.
//Turn -60.
//Draw a straight line.
//Turn -60.
//Draw a straight line.
void Gosper::rightCurve( int level, float d ) {
    if ( level > 0 ) {
        turn(RIGHT);
        leftCurve(level-1,d);
        turn(LEFT);
        rightCurve(level-1,d);
        rightCurve(level-1,d);
        turn(LEFT);
        turn(LEFT);
        rightCurve(level-1,d);
        turn(LEFT);
        leftCurve(level-1,d);
        turn(RIGHT);
        turn(RIGHT);
        leftCurve(level-1,d);
        turn(RIGHT);
        rightCurve(level-1,d);
    }
    else
        draw( d );
}

//------------------------- rightCurve ----------------------------
//Turn -60.
//Draw a level-1 left curve.
//Turn +60.
//Draw a level-1 right curve.
//Draw a level-1 right curve.
//Turn +60.
//Turn +60.
//Draw a level-1 right curve.
//Turn +60.
//Draw a level-1 left curve.
//Turn -60.
//Turn -60.
//Draw a level-1 left curve.
//Turn -60.
//Draw a level-1 right curve.
void Gosper::leftCurve( int level, float d ) {
    if ( level > 0 ) {
        leftCurve(level-1,d);
        turn(LEFT);
        rightCurve(level-1,d);
        turn(LEFT);
        turn(LEFT);
        rightCurve(level-1,d);
        turn(RIGHT);
        leftCurve(level-1,d);
        turn(RIGHT);
        turn(RIGHT);
        leftCurve(level-1,d);
        leftCurve(level-1,d);
        turn(RIGHT);
        rightCurve(level-1,d);
        turn(LEFT);
    }
    else
        draw( d );
}