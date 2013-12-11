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
    ss << setw(w) <<       "RAW: " << Utils::format(nowLocal, fmt) << endl;
    ss << setw(w) <<        "MS: " << Utils::format(Utils::floor(nowLocal, Poco::Timespan::MILLISECONDS), fmt) << endl;
    ss << setw(w) <<   "SECONDS: " << Utils::format(Utils::floor(nowLocal, Poco::Timespan::SECONDS), fmt) << endl;
    ss << setw(w) <<   "MINUTES: " << Utils::format(Utils::floor(nowLocal, Poco::Timespan::MINUTES), fmt) << endl;
    ss << setw(w) <<     "HOURS: " << Utils::format(Utils::floor(nowLocal, Poco::Timespan::HOURS), fmt) << endl;
    ss << setw(w) <<      "DAYS: " << Utils::format(Utils::floor(nowLocal, Poco::Timespan::DAYS), fmt) << endl;

    ss << endl;
    ss << endl;

    ss << setw(w) << "ceiling(): " << endl;
    ss << setw(w) <<       "RAW: " << Utils::format(nowLocal, fmt) << endl;
    ss << setw(w) <<        "MS: " << Utils::format(Utils::ceiling(nowLocal, Poco::Timespan::MILLISECONDS), fmt) << endl;
    ss << setw(w) <<   "SECONDS: " << Utils::format(Utils::ceiling(nowLocal, Poco::Timespan::SECONDS), fmt) << endl;
    ss << setw(w) <<   "MINUTES: " << Utils::format(Utils::ceiling(nowLocal, Poco::Timespan::MINUTES), fmt) << endl;
    ss << setw(w) <<     "HOURS: " << Utils::format(Utils::ceiling(nowLocal, Poco::Timespan::HOURS), fmt) << endl;
    ss << setw(w) <<      "DAYS: " << Utils::format(Utils::ceiling(nowLocal, Poco::Timespan::DAYS), fmt) << endl;

    ss << endl;
    ss << endl;

    ss << setw(w) <<   "round(): " << endl;
    ss << setw(w) <<       "RAW: " << Utils::format(nowLocal, fmt) << endl;
    ss << setw(w) <<        "MS: " << Utils::format(Utils::round(nowLocal, Poco::Timespan::MILLISECONDS), fmt) << endl;
    ss << setw(w) <<   "SECONDS: " << Utils::format(Utils::round(nowLocal, Poco::Timespan::SECONDS), fmt) << endl;
    ss << setw(w) <<   "MINUTES: " << Utils::format(Utils::round(nowLocal, Poco::Timespan::MINUTES), fmt) << endl;
    ss << setw(w) <<     "HOURS: " << Utils::format(Utils::round(nowLocal, Poco::Timespan::HOURS), fmt) << endl;
    ss << setw(w) <<      "DAYS: " << Utils::format(Utils::round(nowLocal, Poco::Timespan::DAYS), fmt) << endl;
    
    ss << endl;

    Poco::LocalDateTime future = nowLocal + Period::Year();

    ss << setw(w) << "ONE YEAR FROM NOW: " << Utils::format(future) << endl;

    ss << endl;

    ofDrawBitmapStringHighlight(ss.str(), ofVec2f(30,30));
}
