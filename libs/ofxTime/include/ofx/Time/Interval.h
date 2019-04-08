//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <iostream>
#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"


namespace ofx {
namespace Time {


/// \brief Interval represents a timespan defined bounded by timestamps.
///
/// The start Poco::Timestamp is guaranteed <= end Poco::Timestamp.
/// Poco does not offer full support for Poco::Timestamp < 0.
/// The behavior of Interval for values < 0 is undefined.
///
/// Comparison operators operate on one or both end points.  Equality
/// operators compare both end points.  Comparison operators >, <, >=, <=
/// compare only the start end point and are primarily useful for sorting.
///
/// \note The relationship `start <= end` is enforced by this class.
class Interval
{
public:
    /// \brief Creates an empty Interval.
    ///
    /// Both start and end are set to with Poco::Timestamp(0).
    Interval();

    /// \brief Creates an Interval with a start and a end Poco::Timestamp.
    /// \param start is starting timestamp.
    /// \param end is the ending timestamp.
    /// \note If `start > end`, the `start` and `end` are
    /// swapped to guaruntee the relationship `start <= end`.
    Interval(const Poco::Timestamp& start, const Poco::Timestamp& end);

    /// \brief Creates an Interval with a start and a end Poco::DateTime.
    /// \param start is starting datetime.
    /// \param end is the ending datetime.
    /// \note If `start > end`, the `start` and `end` are
    /// swapped to guaruntee the relationship `start <= end`.
    Interval(const Poco::DateTime& start, const Poco::DateTime& end);

    /// \brief Creates an Interval from the center.
    /// \param center is the center of the interval.
    /// \param timespan is the total duration of the interval.  The
    /// relationship `start == center - timespan / 2` and `end == center +
    /// timespan / 2` is enforced.
    Interval(const Poco::Timestamp& center, const Poco::Timespan& timespan);

    /// \brief Destroys the Interval.
    virtual ~Interval();

    /// \brief Sets the Interval bounds.
    /// \param start is starting timestamp.
    /// \param end is the ending timestamp.
    /// \note If `start > end`, the `start` and `end` are
    /// swapped to guaruntee the relationship `start <= end`.
    void set(const Poco::Timestamp& start, const Poco::Timestamp& end);

    /// \brief Sets the Interval from the center.
    /// \param center is the center of the interval.
    /// \param timespan is the total duration of the interval.  The
    /// relationship `start == center - timespan / 2` and `end == center +
    /// timespan / 2` is enforced.
    void setFromCenter(const Poco::Timestamp& center,
                       const Poco::Timespan& timespan);

    /// \returns the Interval start timestamp.
    Poco::Timestamp getStart() const;

    /// \returns the Interval end timestamp.
    Poco::Timestamp getEnd() const;

    /// \brief Return a linearly interpolated timestamp.
    /// \param amount usually [0, 1], where 0 == start and 1 == end.
    /// \param clamp clamps amount in the range 0 <= amount <= 1.
    /// \returns the linearly mapped timestamp.
    Poco::Timestamp lerp(float amount, bool clamp = true) const;

    /// \returns a floating point representing a linear mapping
    /// where start = 0 and end = 1.  When clamping is == true,
    /// input times are clamped from start to end, ensuring that
    /// the returned values stay within a 0-1 Interval.
    float map(const Poco::Timestamp& time, bool clamp = true) const;

    /// \brief Converts the given timestamp to a 0-1 Interval, where 0 == start
    /// and 1 == end.  Equivaluent to calling map() with clamp == true.
    /// \param time the timestamp to noramlize.
    /// \returns the noramlized 0-1 timestamp for this interval.
    float normalize(const Poco::Timestamp& time) const;

    /// \returns the Poco::Timespan represented by end - start;
    Poco::Timespan getTimespan() const;

    /// \returns true iff the given Poco::Timestamp is contained within
    /// the Interval.  The comparison is inclusive of the endpoints.
    bool contains(const Poco::Timestamp& timestamp) const;

    /// \returns true iff the given Interval is completely contained within
    /// the Interval.  The comparison is inclusive of the endpoints.
    bool contains(const Interval& other) const;

    /// \returns true iff any portion of the given Interval
    /// with this Interval intersects with the
    bool intersects(const Interval& other) const;

    /// \returns true iff the endpoints of the given Interval
    /// are exactly equal to the endpoints of this Interval.
    bool operator == (const Interval& other) const;

    /// \returns true iff the endpoints of the given Interval
    /// are not exactly equal to the endpoints of this Interval.
    bool operator != (const Interval& other) const;

    /// \returns true iff the start is greater than the given Interval's start.
    bool operator >  (const Interval& other) const;

    /// \returns true iff the start is greater than
    /// or equal to the given Interval's start.
    bool operator >= (const Interval& other) const;

    /// \returns true iff the start is less than the given Interval's start.
    bool operator <  (const Interval& other) const;

    /// \returns true iff the start is less than or equal
    /// to the given Interval's start.
    bool operator <= (const Interval& other) const;

    /// \returns true iff the Interval0  is completely contained within the
    /// Interval.  The comparison is inclusive of the endpoints.
    static bool intersects(const Interval& interval0, const Interval& interval1);

    /// \returns a Poco::Timestamp corresponding to a linear mapping in
    /// the given Interval where 0 == start and 1 == end.
    /// When clamping is == true, input amounts are clamped from 0-1,
    /// ensuring that the returned values stay within Interval.
    static Poco::Timestamp lerp(const Interval& interval, float amount, bool clamp = true);

    /// \returns a floating point representing a linear mapping of Interval
    /// where start = 0 and end = 1.  When clamping is == true,
    /// input times are clamped from start to end, ensuring that
    /// the returned values stay within a 0-1 Interval.
    static float map(const Interval& interval, const Poco::Timestamp& time, bool clamp = true);

    /// \brief Converts the given timestamp to a 0-1 Interval, where 0 == start
    /// and 1 == end.  Equivaluent to calling map() with clamp == true.
    static float normalize(const Interval& interval, const Poco::Timestamp& time);

private:
    Poco::Timestamp _start;
        ///< \brief The start value of the Interval.

    Poco::Timestamp _end;
        ///< \brief The end value of the Interval.

};


} } // namespace ofx::Time
