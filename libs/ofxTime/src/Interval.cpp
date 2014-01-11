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


#include "ofx/Time/Interval.h"


namespace ofx {
namespace Time {
    

Interval::Interval():
    _start(0),
    _end(0)
{
}


Interval::Interval(const Poco::Timestamp& min, const Poco::Timestamp& max):
    _start(min),
    _end(max)
{
    if (_start > _end)
    {
        std::swap(_start, _end);
    }
}


Interval::Interval(const Poco::Timestamp& center, const Poco::Timespan& timespan):
    _start(center - timespan.totalMicroseconds() / 2),
    _end(center + timespan.totalMicroseconds() / 2)
{
    if (_start > _end)
    {
        std::swap(_start, _end);
    }
}


Interval::~Interval()
{
}


void Interval::set(const Poco::Timestamp& start, const Poco::Timestamp& end)
{
    _start = start;
    _end = end;

    if (_start > _end)
    {
        std::swap(_start, _end);
    }
}


void Interval::setFromCenter(const Poco::Timestamp& center, const Poco::Timespan& timespan)
{
    _start = (center - timespan.totalMicroseconds() / 2);
    _end = (center + timespan.totalMicroseconds() / 2);

    if (_start > _end)
    {
        std::swap(_start, _end);
    }
}


Poco::Timestamp Interval::getStart() const
{
    return _start;
}


Poco::Timestamp Interval::getEnd() const
{
    return _end;
}


Poco::Timestamp Interval::lerp(float value, bool clamp) const
{
    return lerp(*this, value, clamp);
}


float Interval::map(const Poco::Timestamp& time, bool clamp) const
{
    return map(*this, time, clamp);
}


float Interval::normalize(const Poco::Timestamp& time) const
{
    return map(*this, time, true);
}


Poco::Timespan Interval::getTimespan() const
{
    return Poco::Timespan(_end - _start);
}


bool Interval::contains(const Poco::Timestamp& timestamp) const
{
    return (timestamp <= _end && timestamp >= _start);
}


bool Interval::contains(const Interval& interval) const
{
    return contains(interval.getStart()) && contains(interval.getEnd());
}


bool Interval::intersects(const Interval& interval) const
{
    return intersects(*this, interval);
}


bool Interval::intersects(const Interval& interval0, const Interval& interval1)
{
    return interval0.contains(interval1.getStart()) ||
           interval0.contains(interval1.getEnd()) ||
           interval1.contains(interval0.getStart()) ||
           interval1.contains(interval0.getEnd());
}


bool Interval::operator == (const Interval& other) const
{
    return (_start == other._start) && (_end == other._end);
}


bool Interval::operator != (const Interval& other) const
{
    return (_start != other._start) || (_end != other._end);
}
    

bool Interval::operator >  (const Interval& other) const
{
    return _start > other._start;
}


bool Interval::operator >= (const Interval& other) const
{
    return _start >= other._start;
}


bool Interval::operator <  (const Interval& other) const
{
    return _start < other._start;
}


bool Interval::operator <= (const Interval& other) const
{
    return _start <= other._start;
}


Poco::Timestamp Interval::lerp(const Interval& interval, float amount, bool clamp)
{
    if (clamp)
    {
        if (amount > 1) amount = 1;
        if (amount < 0) amount = 0;
    }

    return interval.getStart() + (interval.getEnd() - interval.getStart()) * amount;
}


float Interval::map(const Interval& interval, const Poco::Timestamp& time, bool clamp)
{
    float amount = (float)(time - interval.getStart()) / (interval.getEnd() - interval.getStart());

    if (clamp)
    {
        if (amount > 1) amount = 1;
        if (amount < 0) amount = 0;
    }

    return amount;
}


float Interval::normalize(const Interval& Interval, const Poco::Timestamp& time)
{
    return map(Interval, time, true);
}


} } // namespace ofx::Time
