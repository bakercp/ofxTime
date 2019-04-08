//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::draw()
{
    // TODO: add example for any arbitrary ofx::Time::Period

    ofBackgroundGradient(ofColor::white, ofColor::black);

    Poco::Timestamp now;
    Poco::LocalDateTime nowLocal(now);

    int w = 14;

    std::stringstream ss;

    std::string fmt = Poco::DateTimeFormat::RFC1123_FORMAT + " %F ";


    ss << setw(w) <<   "floor(): " << endl;
    ss << setw(w) <<       "RAW: " << ofxTime::Utils::format(nowLocal, fmt) << endl;
    ss << setw(w) <<        "MS: " << ofxTime::Utils::format(ofxTime::Utils::floor(nowLocal, Poco::Timespan::MILLISECONDS), fmt) << endl;
    ss << setw(w) <<   "SECONDS: " << ofxTime::Utils::format(ofxTime::Utils::floor(nowLocal, Poco::Timespan::SECONDS), fmt) << endl;
    ss << setw(w) <<   "MINUTES: " << ofxTime::Utils::format(ofxTime::Utils::floor(nowLocal, Poco::Timespan::MINUTES), fmt) << endl;
    ss << setw(w) <<     "HOURS: " << ofxTime::Utils::format(ofxTime::Utils::floor(nowLocal, Poco::Timespan::HOURS), fmt) << endl;
    ss << setw(w) <<      "DAYS: " << ofxTime::Utils::format(ofxTime::Utils::floor(nowLocal, Poco::Timespan::DAYS), fmt) << endl;

    ss << endl;
    ss << endl;

    ss << setw(w) << "ceiling(): " << endl;
    ss << setw(w) <<       "RAW: " << ofxTime::Utils::format(nowLocal, fmt) << endl;
    ss << setw(w) <<        "MS: " << ofxTime::Utils::format(ofxTime::Utils::ceiling(nowLocal, Poco::Timespan::MILLISECONDS), fmt) << endl;
    ss << setw(w) <<   "SECONDS: " << ofxTime::Utils::format(ofxTime::Utils::ceiling(nowLocal, Poco::Timespan::SECONDS), fmt) << endl;
    ss << setw(w) <<   "MINUTES: " << ofxTime::Utils::format(ofxTime::Utils::ceiling(nowLocal, Poco::Timespan::MINUTES), fmt) << endl;
    ss << setw(w) <<     "HOURS: " << ofxTime::Utils::format(ofxTime::Utils::ceiling(nowLocal, Poco::Timespan::HOURS), fmt) << endl;
    ss << setw(w) <<      "DAYS: " << ofxTime::Utils::format(ofxTime::Utils::ceiling(nowLocal, Poco::Timespan::DAYS), fmt) << endl;

    ss << endl;
    ss << endl;

    ss << setw(w) <<   "round(): " << endl;
    ss << setw(w) <<       "RAW: " << ofxTime::Utils::format(nowLocal, fmt) << endl;
    ss << setw(w) <<        "MS: " << ofxTime::Utils::format(ofxTime::Utils::round(nowLocal, Poco::Timespan::MILLISECONDS), fmt) << endl;
    ss << setw(w) <<   "SECONDS: " << ofxTime::Utils::format(ofxTime::Utils::round(nowLocal, Poco::Timespan::SECONDS), fmt) << endl;
    ss << setw(w) <<   "MINUTES: " << ofxTime::Utils::format(ofxTime::Utils::round(nowLocal, Poco::Timespan::MINUTES), fmt) << endl;
    ss << setw(w) <<     "HOURS: " << ofxTime::Utils::format(ofxTime::Utils::round(nowLocal, Poco::Timespan::HOURS), fmt) << endl;
    ss << setw(w) <<      "DAYS: " << ofxTime::Utils::format(ofxTime::Utils::round(nowLocal, Poco::Timespan::DAYS), fmt) << endl;

    ss << endl;

    Poco::LocalDateTime future = nowLocal + ofxTime::Period::Year();

    ss << setw(w) << "ONE YEAR FROM NOW: " << ofxTime::Utils::format(future) << endl;

    ss << endl;

    ofDrawBitmapStringHighlight(ss.str(), 30, 30);
}
