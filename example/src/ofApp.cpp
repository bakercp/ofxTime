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


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);

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
    range0.set(min0.timestamp(), max0.timestamp());
    range1.set(min1.timestamp(), max1.timestamp());

    std::string range0Min = Poco::DateTimeFormatter::format(range0.getMinimum(), Poco::DateTimeFormat::RFC1036_FORMAT);
    std::string range0Max = Poco::DateTimeFormatter::format(range0.getMaximum(), Poco::DateTimeFormat::RFC1036_FORMAT);
    std::string range1Min = Poco::DateTimeFormatter::format(range1.getMinimum(), Poco::DateTimeFormat::RFC1036_FORMAT);
    std::string range1Max = Poco::DateTimeFormatter::format(range1.getMaximum(), Poco::DateTimeFormat::RFC1036_FORMAT);

    ofLogNotice("ofApp::setup()") << "range0: " << range0Min << " - " << range0Max;
    ofLogNotice("ofApp::setup()") << "range1: " << range1Min << " - " << range1Max;

}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);



    float y0 = ofMap(range1.getMinimum().utcTime(), range0.getMinimum().utcTime(), range0.getMaximum().utcTime(), 0, ofGetHeight());
    float y1 = ofMap(range1.getMaximum().utcTime(), range0.getMinimum().utcTime(), range0.getMaximum().utcTime(), 0, ofGetHeight());

    ofFill();
    ofSetColor(ofColor::yellow);
    ofRect(0, 0, ofGetWidth() / 4, ofGetHeight());

    ofFill();
    ofSetColor(ofColor::red);
    ofRect(0, y0, ofGetWidth() / 4, y1 - y0);


    std::string range0Min = Poco::DateTimeFormatter::format(range0.getMinimum(), Poco::DateTimeFormat::RFC1036_FORMAT);
    std::string range0Max = Poco::DateTimeFormatter::format(range0.getMaximum(), Poco::DateTimeFormat::RFC1036_FORMAT);
    std::string range1Min = Poco::DateTimeFormatter::format(range1.getMinimum(), Poco::DateTimeFormat::RFC1036_FORMAT);
    std::string range1Max = Poco::DateTimeFormatter::format(range1.getMaximum(), Poco::DateTimeFormat::RFC1036_FORMAT);

    ofDrawBitmapStringHighlight(range0Min, ofVec2f(ofGetWidth() / 4, + 14));
    ofDrawBitmapStringHighlight(range0Max, ofVec2f(ofGetWidth() / 4, ofGetHeight()));
    ofDrawBitmapStringHighlight(range1Min, ofVec2f(ofGetWidth() / 4, y0));
    ofDrawBitmapStringHighlight(range1Max, ofVec2f(ofGetWidth() / 4, y1));


    ofSetColor(0,255,0);
    ofLine(0, ofGetMouseY(), ofGetWidth(), ofGetMouseY());

    float normalizedMousePosition = ofGetMouseY() / (float)ofGetHeight();

    Poco::Timestamp ts = range0.lerp(normalizedMousePosition);

    std::string ts0 = Poco::DateTimeFormatter::format(ts, Poco::DateTimeFormat::RFC1036_FORMAT);

    ofDrawBitmapStringHighlight(ts0, ofVec2f(ofGetWidth() / 4, ofGetMouseY()));



}
