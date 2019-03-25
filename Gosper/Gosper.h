//
// Created by Jakob Wilter on 10/20/18.
//

#ifndef PROGRAM3RECURSION_GOSPER_H
#define PROGRAM3RECURSION_GOSPER_H

#include "turtle.h"
#include <iostream>
#include <math.h>

using namespace std;

class Gosper : public Turtle {
public:
    Gosper(float initialX = 0.0, float initialY = 0.0, float initialAngle = 0.0);
    void leftCurve(int l, float d);
    void rightCurve(int l, float d);

private:


};


#endif //PROGRAM3RECURSION_GOSPER_H
