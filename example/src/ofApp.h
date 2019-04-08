//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofMain.h"
#include "ofxTime.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();

    ofxTime::Interval interval0;
    ofxTime::Interval interval1;

};
