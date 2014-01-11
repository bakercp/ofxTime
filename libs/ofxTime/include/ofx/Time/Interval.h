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
    /// \brief Interval represents a timespan defined bounded by timestamps.
    /// \details The start Poco::Timestamp is guaranteed <= end Poco::Timestamp.
    /// Poco does not offer full support for Poco::Timestamp < 0.
    /// The behavior of Interval for values < 0 is undefined.
    ///
    /// Comparison operators operate on one or both end points.  Equality
    /// operators compare both end points.  Comparison operators >, <, >=, <=
    /// compare only the start end point and are primarily useful for sorting.
    ///
    /// \note The relationship `start <= end` is enforced by this class.
{
public:
    Interval();
        ///< \brief Creates an empty Interval.
        ///< \details Both start and end are set to with Poco::Timestamp(0).

    Interval(const Poco::Timestamp& start, const Poco::Timestamp& end);
        ///< \brief Creates an Interval with a start and a end Poco::Timestamp.
        ///< \param start is starting timestamp.
        ///< \param end is the ending timestamp.
        ///< \note If `start > end`, the `start` and `end` are
        ///< swapped to guaruntee the relationship `start <= end`.

    Interval(const Poco::Timestamp& center, const Poco::Timespan& timespan);
        ///< \brief Creates an Interval from the center.
        ///< \param center is the center of the interval.
        ///< \param timespan is the total duration of the interval.  The
        ///< relationship `start == center - timespan / 2` and `end == center +
        ///< timespan / 2` is enforced.

    virtual ~Interval();
        ///< \brief Destroys the Interval.

    void set(const Poco::Timestamp& start, const Poco::Timestamp& end);
        ///< \brief Sets the Interval bounds.
        ///< \param start is starting timestamp.
        ///< \param end is the ending timestamp.
        ///< \note If `start > end`, the `start` and `end` are
        ///< swapped to guaruntee the relationship `start <= end`.

    void setFromCenter(const Poco::Timestamp& center,
                       const Poco::Timespan& timespan);
        ///< \brief Sets the Interval from the center.
        ///< \param center is the center of the interval.
        ///< \param timespan is the total duration of the interval.  The
        ///< relationship `start == center - timespan / 2` and `end == center +
        ///< timespan / 2` is enforced.

    Poco::Timestamp getStart() const;
        ///< \returns the Interval start timestamp.

    Poco::Timestamp getEnd() const;
        ///< \returns the Interval end timestamp.

    Poco::Timestamp lerp(float amount, bool clamp = true) const;
        ///< \brief Return a linearly interpolated timestamp.
        ///< \param amount usually [0, 1], where 0 == start and 1 == end.
        ///< \param clamp clamps amount in the range 0 <= amount <= 1.
        ///< \returns the linearly mapped timestamp.

    float map(const Poco::Timestamp& time, bool clamp = true) const;
        ///< Return a floating point representing a linear mapping
        ///< where start = 0 and end = 1.  When clamping is == true,
        ///< input times are clamped from start to end, ensuring that
        ///< the returned values stay within a 0-1 Interval.

    float normalize(const Poco::Timestamp& time) const;
        ///< Converts the given timestamp to a 0-1 Interval, where 0 == start
        ///< and 1 == end.  Equivaluent to calling map() with clamp == true.

    Poco::Timespan getTimespan() const;
        ///< Returns the Poco::Timespan represented by end - start;

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
        ///< Returns true iff the start is greater
        ///< than the given Interval's start.

    bool operator >= (const Interval& other) const;
        ///< Returns true iff the start is greater than
        ///< or equal to the given Interval's start.

    bool operator <  (const Interval& other) const;
        ///< Returns true iff the start is less
        ///< than the given Interval's start.

    bool operator <= (const Interval& other) const;
        ///< Returns true iff the start is less than
        ///< or equal to the given Interval's start.

    static bool intersects(const Interval& interval0, const Interval& interval1);
        ///< Returns true iff the Interval0  is completely contained within the
        ///< Interval.  The comparison is inclusive of the endpoints.

    static Poco::Timestamp lerp(const Interval& interval, float amount, bool clamp = true);
        ///< Return a Poco::Timestamp corresponding to a linear mapping in
        ///< the given Interval where 0 == start and 1 == end.
        ///< When clamping is == true, input amounts are clamped from 0-1,
        ///< ensuring that the returned values stay within Interval.

    static float map(const Interval& interval, const Poco::Timestamp& time, bool clamp = true);
        ///< Return a floating point representing a linear mapping of Interval
        ///< where start = 0 and end = 1.  When clamping is == true,
        ///< input times are clamped from start to end, ensuring that
        ///< the returned values stay within a 0-1 Interval.

    static float normalize(const Interval& interval, const Poco::Timestamp& time);
        ///< Converts the given timestamp to a 0-1 Interval, where 0 == start
        ///< and 1 == end.  Equivaluent to calling map() with clamp == true.

private:
    Poco::Timestamp _start; ///< The start value of the Interval.
    Poco::Timestamp _end; ///< The end value of the Interval.

};


} } // namespace ofx::Time
