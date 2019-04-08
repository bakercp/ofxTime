//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/Time/Interval.h"


namespace ofx {
namespace Time {
    

Interval::Interval():
    _start(0),
    _end(0)
{
}


Interval::Interval(const Poco::Timestamp& start, const Poco::Timestamp& end):
    _start(start),
    _end(end)
{
    if (_start > _end)
    {
        std::swap(_start, _end);
    }
}


Interval::Interval(const Poco::DateTime& start, const Poco::DateTime& end):
    _start(start.timestamp()),
    _end(end.timestamp())
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
