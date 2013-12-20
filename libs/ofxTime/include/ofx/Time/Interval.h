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


#pragma once


#include <iostream>
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"


namespace ofx {
namespace Time {


class Interval
    /// Interval represents a timespan defined bounded by timestamps.
    /// The minimum Poco::Timestamp is guaranteed <= maximum Poco::Timestamp.
    /// Poco does not offer full support for Poco::Timestamp < 0.
    /// The behavior of Interval for values < 0 is undefined.
    ///
    /// Comparison operators operate on one or both end points.  Equality
    /// operators compare both end points.  Comparison operators >, <, >=, <=
    /// compare only the minimum end point and are primarily useful for sorting.
{
public:
    Interval();
        ///< Creates an empty Interval.
        ///< Both minimum and maximum are set to with Poco::Timestamp(0).

    Interval(const Poco::Timestamp& minimum, const Poco::Timestamp& maximum);
        ///< Creates an Interval with a minimum and a maximum Poco::Timestamp.
        ///< If minimum is not <= maximum, the two values are swapped to
        ///< guarantee that minimum <= maximum.

    Interval(const Poco::Timestamp& center, const Poco::Timespan& timespan);
        ///< Interval represents a timespan defined by two timestamps.

    virtual ~Interval();
        ///< Destroys the Interval.

    void set(const Poco::Timestamp& minimum, const Poco::Timestamp& maximum);
        ///< Sets the Interval bounds.
        ///< If minimum is not <= maximum, the two values are swapped to
        ///< guarantee that minimum <= maximum.

    void setFromCenter(const Poco::Timestamp& center,
                       const Poco::Timespan& timespan);
        ///< Sets the Interval from the center.
        ///< The minimum value becomes center - timespan / 2.
        ///< The maximum value becomes center + timespan / 2.

    Poco::Timestamp getStart() const;
        ///< Returns the Interval beginning.

    Poco::Timestamp getEnd() const;
        ///< Returns the Interval end.

    Poco::Timestamp lerp(float amount, bool clamp = true) const;
        ///< Return a Poco::Timestamp corresponding to a linear mapping
        ///< where 0 == minimum and 1 == maximum.  When clamping is == true,
        ///< input amounts are clamped from 0-1, ensuring that the returned
        ///< values stay within Interval.

    float map(const Poco::Timestamp& time, bool clamp = true) const;
        ///< Return a floating point representing a linear mapping
        ///< where minimum = 0 and maximum = 1.  When clamping is == true,
        ///< input times are clamped from minimum to maximum, ensuring that
        ///< the returned values stay within a 0-1 Interval.

    float normalize(const Poco::Timestamp& time) const;
        ///< Converts the given timestamp to a 0-1 Interval, where 0 == minimum
        ///< and 1 == maximum.  Equivaluent to calling map() with clamp == true.

    Poco::Timespan getTimespan() const;
        ///< Returns the Poco::Timespan represented by maximum - minimum;

    bool contains(const Poco::Timestamp& timestamp) const;
        ///< Returns true iff the given Poco::Timestamp is contained within
        ///< the Interval.  The comparison is inclusive of the endpoints.

    bool contains(const Interval& other) const;
        ///< Returns true iff the given Interval is completely contained within
        ///< the Interval.  The comparison is inclusive of the endpoints.

    bool intersects(const Interval& other) const;
        ///< Returns true iff any portion of the given Interval
        ///< with this Interval intersects with the

    bool operator == (const Interval& other) const;
        ///< Returns true iff the endpoints of the given Interval
        ///< are exactly equal to the endpoints of this Interval.

    bool operator != (const Interval& other) const;
        ///< Returns true iff the endpoints of the given Interval
        ///< are not exactly equal to the endpoints of this Interval.

    bool operator >  (const Interval& other) const;
        ///< Returns true iff the minimum is greater
        ///< than the given Interval's minimum.

    bool operator >= (const Interval& other) const;
        ///< Returns true iff the minimum is greater than
        ///< or equal to the given Interval's minimum.

    bool operator <  (const Interval& other) const;
        ///< Returns true iff the minimum is less
        ///< than the given Interval's minimum.

    bool operator <= (const Interval& other) const;
        ///< Returns true iff the minimum is less than
        ///< or equal to the given Interval's minimum.

    static bool intersects(const Interval& interval0, const Interval& interval1);
        ///< Returns true iff the Interval0  is completely contained within the
        ///< Interval.  The comparison is inclusive of the endpoints.

    static Poco::Timestamp lerp(const Interval& interval, float amount, bool clamp = true);
        ///< Return a Poco::Timestamp corresponding to a linear mapping in
        ///< the given Interval where 0 == minimum and 1 == maximum.
        ///< When clamping is == true, input amounts are clamped from 0-1,
        ///< ensuring that the returned values stay within Interval.

    static float map(const Interval& interval, const Poco::Timestamp& time, bool clamp = true);
        ///< Return a floating point representing a linear mapping of Interval
        ///< where minimum = 0 and maximum = 1.  When clamping is == true,
        ///< input times are clamped from minimum to maximum, ensuring that
        ///< the returned values stay within a 0-1 Interval.

    static float normalize(const Interval& interval, const Poco::Timestamp& time);
        ///< Converts the given timestamp to a 0-1 Interval, where 0 == minimum
        ///< and 1 == maximum.  Equivaluent to calling map() with clamp == true.

private:
    Poco::Timestamp _minimum; ///< The minimum value of the Interval.
    Poco::Timestamp _maximum; ///< The maximum value of the Interval.

};


} } // namespace ofx::Time
