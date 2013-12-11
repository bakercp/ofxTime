// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);
    ofEnableAlphaBlending();

    const std::string TWITTER_DATE_FORMAT = "%w %b %f %H:%M:%S %Z %Y";

    std::string ts0 = "2000-01-01T12:00:00+01:00";        // Poco::DateTimeFormat::ISO8601_FORMAT
    std::string ts1 = "Wednesday, 1 Jan 20 12:00:00 GMT"; // Poco::DateTimeFormat::RFC1036_FORMAT
    std::string ts2 = "2018-01-01T17:00:00.000000+05:00"; // Poco::DateTimeFormat::ISO8601_FRAC_FORMAT
    std::string ts3 = "Tue Nov 12 23:14:54 +1100 2013";   // custom TWITTER_DATE_FORMAT

    int tzd0 = 0;
    int tzd1 = 0;
    int tzd2 = 0;
    int tzd3 = 0;

    Poco::DateTime min0;
    Poco::DateTime max0;
    Poco::DateTime min1;
    Poco::DateTime max1;

    try
    {
        // try to auto detect a known format
        min0 = Poco::DateTimeParser::parse(ts0, tzd0);

        // try to auto detect a known format
        max0 = Poco::DateTimeParser::parse(ts1, tzd1);

        // parse with a known format
        Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FRAC_FORMAT, ts2, min1, tzd2);

        // parse with a custom format
        Poco::DateTimeParser::parse(TWITTER_DATE_FORMAT, ts3, max1, tzd3);

        // we want to work with UTC time, rather than the local time parsed by
        // the Poco::DateTimeParser.  it is easy to convert by simply calling
        // Poco::DateTimeParser::makeUTC() with the time zone difference (in seconds)
        // calculated by the parser.

        min0.makeUTC(tzd0);
        max0.makeUTC(tzd1);
        min1.makeUTC(tzd2);
        max1.makeUTC(tzd3);
    }
    catch (const Poco::SyntaxException& exc)
    {
        ofLogError("ofApp::setup()") << "Syntax exception: " << exc.displayText();
    }

    // set up our ranges.  the Time::Range::set() function will order the
    // Poco::Timestamps appropriately.
    interval0.set(min0.timestamp(), max0.timestamp());
    interval1.set(min1.timestamp(), max1.timestamp());

    std::string range0Min = Utils::format(interval0.getStart());
    std::string range0Max = Utils::format(interval0.getEnd());
    std::string range1Min = Utils::format(interval1.getStart());
    std::string range1Max = Utils::format(interval1.getEnd());

    ofLogNotice("ofApp::setup()") << "range0: " << range0Min << " - " << range0Max;
    ofLogNotice("ofApp::setup()") << "range1: " << range1Min << " - " << range1Max;

}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);

    // get the screen Y values of range1
    float y0 = ofMap(interval1.getStart().utcTime(), interval0.getStart().utcTime(), interval0.getEnd().utcTime(), 0, ofGetHeight());
    float y1 = ofMap(interval1.getEnd().utcTime(), interval0.getStart().utcTime(), interval0.getEnd().utcTime(), 0, ofGetHeight());

    // draw range0
    ofFill();
    ofSetColor(ofColor::yellow, 80);
    ofRectRounded(0, 0, ofGetWidth() / 4, ofGetHeight(), 5);

    // draw range1
    ofFill();
    ofSetColor(ofColor::red, 80);
    ofRectRounded(0, y0, ofGetWidth() / 4, y1 - y0, 5);

    // get the range boundaries as formatted strings
    std::string range0Min = Utils::format(interval0.getStart());
    std::string range0Max = Utils::format(interval0.getEnd());
    std::string range1Min = Utils::format(interval1.getStart());
    std::string range1Max = Utils::format(interval1.getEnd());

    // draw the range boundaries
    ofDrawBitmapStringHighlight(range0Min, ofVec2f(ofGetWidth() / 4, + 14));
    ofDrawBitmapStringHighlight(range0Max, ofVec2f(ofGetWidth() / 4, ofGetHeight()));
    ofDrawBitmapStringHighlight(range1Min, ofVec2f(ofGetWidth() / 4, y0));
    ofDrawBitmapStringHighlight(range1Max, ofVec2f(ofGetWidth() / 4, y1));

    // draw a line based on the cursor position
    ofSetColor(255);
    ofLine(0, ofGetMouseY(), ofGetWidth(), ofGetMouseY());

    // calculate the noramlized cursor position
    float normalizedMousePosition = ofGetMouseY() / (float)ofGetHeight();

    // use the range0's lerp function to interpolate the date under the mouse
    Poco::Timestamp ts = interval0.lerp(normalizedMousePosition);

    // formate the interpolated date to a string
    std::string ts0 = Utils::format(ts);

    // draw the interpolated date
    ofDrawBitmapStringHighlight(ts0, ofVec2f(ofGetWidth() / 4, ofGetMouseY()));

}
