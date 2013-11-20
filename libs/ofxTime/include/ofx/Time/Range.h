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


#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"


namespace ofx {
namespace Time {


// TODO: template on ofRange.h
class Range
{
public:
    Range();
    Range(const Poco::Timestamp& minimum, const Poco::Timestamp& maximum);

    virtual ~Range();

    void set(const Poco::Timestamp& minimum, const Poco::Timestamp& maximum);

    Poco::Timestamp getMinimum() const;
    Poco::Timestamp getMaximum() const;

    Poco::Timestamp lerp(double amount, bool clamp = true) const;

    Poco::Timespan getTimespan() const;

    bool contains(const Poco::Timestamp& timestamp) const;
    bool contains(const Range& range) const;

    bool intersects(const Range& range) const;

    static bool intersects(const Range& range0, const Range& range1);

    static Poco::Timestamp lerp(const Range& range, double amount, bool clamp = true);


private:
    Poco::Timestamp _minimum;
    Poco::Timestamp _maximum;
    
};


} } // namespace ofx::Time
