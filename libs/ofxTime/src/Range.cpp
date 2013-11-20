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


#include "ofx/Time/Range.h"


namespace ofx {
namespace Time {
    

Range::Range():
    _minimum(0),
    _maximum(0)
{
}

Range::Range(const Poco::Timestamp& min, const Poco::Timestamp& max):
    _minimum(min),
    _maximum(max)
{
    if (_minimum > _maximum)
    {
        std::swap(_minimum, _maximum);
    }
}

Range::~Range()
{
}

void Range::set(const Poco::Timestamp& minimum, const Poco::Timestamp& maximum)
{
    _minimum = minimum;
    _maximum = maximum;

    if (_minimum > _maximum)
    {
        std::swap(_minimum, _maximum);
    }
}

Poco::Timestamp Range::getMinimum() const
{
    return _minimum;
}

Poco::Timestamp Range::getMaximum() const
{
    return _maximum;
}

Poco::Timestamp Range::lerp(double value, bool clamp) const
{
    return lerp(*this, value, clamp);
}

Poco::Timespan Range::getTimespan() const
{
    return Poco::Timespan(_maximum - _minimum);
}

bool Range::contains(const Poco::Timestamp& timestamp) const
{
    return (timestamp <= _maximum && timestamp >= _minimum);
}

bool Range::contains(const Range& range) const
{
    return contains(range.getMinimum()) && contains(range.getMaximum());
}

bool Range::intersects(const Range& range) const
{
    return intersects(*this, range);
}

bool Range::intersects(const Range& range0, const Range& range1)
{
    return range0.contains(range1.getMinimum()) ||
           range0.contains(range1.getMaximum()) ||
           range1.contains(range0.getMinimum()) ||
           range1.contains(range0.getMaximum());
}

Poco::Timestamp Range::lerp(const Range& range, double amount, bool clamp)
{
    if (clamp)
    {
        if (amount > 1) amount = 1;
        if (amount < 0) amount = 0;
    }

    return range.getMinimum() + (range.getMaximum() - range.getMinimum()) * amount;
}


} } // namespace ofx::Time
