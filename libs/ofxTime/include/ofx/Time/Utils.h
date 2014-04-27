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
#include <vector>
#include <cstdlib>
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/LocalDateTime.h"
#include "Poco/Timespan.h"
#include "Poco/Timestamp.h"
#include "ofx/Time/Interval.h"
#include "ofx/Time/Period.h"
#include "ofLog.h"


namespace ofx {
namespace Time {


/// \brief This class contains a collection of utilities for manipulating
///         Poco::DateTime, Poco::LocalDateTime and Poco::Timestamp.
///
/// Rounding dates and times is timezone dependent.  When dates and times
/// must be rounded with respect to a specific timezone, the Poco::Timestamp
/// or Poco::DateTime should be converted to a Poco::LocalDateTime before
/// rounding.  The UTC equivalent of a Poco::LocalDateTime can then be
/// extracted using the toUtcTimestamp() or toUtcDateTime() functions.
///
/// Notes:
///   - Negative years (years preceding 1 BC) are not supported, thus
///     "truncation" (floor toward zero) is not supported.
///
/// For more information, please see:
///   - http://pocoproject.org/docs/Poco.Timestamp.html
///   - http://pocoproject.org/docs/Poco.DateTime.html
///   - http://pocoproject.org/docs/Poco.LocalDateTime.html
///
/// \todo round to period fields
class Utils
{
public:
    /// \brief Generate instances given known start and stop times.
    ///
    /// Get a fixed number of instances beginning with the "start" time.
    /// Increments are defined by a Period.
    ///
    /// \param start The starting time.
    /// \param numInstances The number of instances to get.
    /// \param period The instance increment size.
    /// \returns a vector of time stamps.
    static std::vector<Poco::Timestamp> getInstances(const Poco::Timestamp& start,
                                                     std::size_t numInstances,
                                                     const Period& period);


    static std::vector<Poco::Timestamp> getInstances(const Poco::Timestamp& start,
                                                     const Poco::Timespan& timespan,
                                                     const Period& period);
        ///< @brief Generate instances given known start and stop times.
        ///< Get all instances beginning with the "start" time
        ///< that occur within the given Timespan.
        ///< Increments are defined by a Period.


    static std::vector<Poco::Timestamp> getInstances(const Poco::Timestamp& start,
                                                     const Poco::Timestamp& end,
                                                     const Period& period);
        ///< Get all instances beginning with the "start" time that happen before
        ///< the given "end" time.
        ///< Increments are defined by a Period.

    static std::vector<Poco::Timestamp> getInstances(const Interval& Interval,
                                                     const Period& period);
        ///< Get all instances beginning with the
        ///< Interval's start time that happen before the
        ///< Interval's "end" time.  Increments are
        ///< defined by an amount and a DateTimeField.

    static Poco::Timestamp toUtcTimestamp(const Poco::LocalDateTime& localDateTime);
        ///< Converts a Poco::LocalDateTime to
        ///< its UTC Poco::Timestamp equivalent.

    static Poco::DateTime toUtcDateTime(const Poco::LocalDateTime& localDateTime);
        ///< Converts a Poco::LocalDateTime to its UTC Poco::DateTime equivalent.

    static Poco::LocalDateTime add(const Poco::LocalDateTime& time,
                                   const Period& period);
        ///< Add an arbitrary period to the given Poco::LocalDateTime.

    static Poco::DateTime add(const Poco::DateTime& time,
                              const Period& period);
        ///< Add an arbitrary period to the given Poco::DateTime.

    static Poco::Timestamp add(const Poco::Timestamp& time,
                               const Period& period);
        ///< Add an arbitrary period to the given Poco::Timestamp.

    static Poco::LocalDateTime addMicroseconds(const Poco::LocalDateTime& time,
                                               int64_t amount);
        ///< Add microseconds to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addMicroseconds(const Poco::DateTime& time,
                                          int64_t amount);
        ///< Add microseconds to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addMicroseconds(const Poco::Timestamp& time,
                                           int64_t amount);
        ///< Add microseconds to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addMilliseconds(const Poco::LocalDateTime& time,
                                               int64_t amount);
        ///< Add milliseconds to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addMilliseconds(const Poco::DateTime& time,
                                          int64_t amount);
        ///< Add milliseconds to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addMilliseconds(const Poco::Timestamp& time,
                                           int64_t amount);
        ///< Add milliseconds to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addSeconds(const Poco::LocalDateTime& time,
                                          int64_t amount);
        ///< Add microseconds to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addSeconds(const Poco::DateTime& time,
                                     int64_t amount);
        ///< Add seconds to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addSeconds(const Poco::Timestamp& time,
                                      int64_t amount);
        ///< Add seconds to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addMinutes(const Poco::LocalDateTime& time,
                                          int64_t amount);
        ///< Add minutes to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addMinutes(const Poco::DateTime& time,
                                     int64_t amount);
        ///< Add minutes to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addMinutes(const Poco::Timestamp& time,
                                      int64_t amount);
        ///< Add minutes to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addHours(const Poco::LocalDateTime& time,
                                        int64_t amount);
        ///< Add hours to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addHours(const Poco::DateTime& time,
                                   int64_t amount);
        ///< Add hours to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addHours(const Poco::Timestamp& time,
                                    int64_t amount);
        ///< Add hours to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addDays(const Poco::LocalDateTime& time,
                                       int64_t amount);
        ///< Add days to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addDays(const Poco::DateTime& time,
                                  int64_t amount);
        ///< Add days to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addDays(const Poco::Timestamp& time,
                                   int64_t amount);
        ///< Add days to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addWeeks(const Poco::LocalDateTime& time,
                                        int64_t amount);
        ///< Add weeks to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addWeeks(const Poco::DateTime& time,
                                   int64_t amount);
        ///< Add weeks to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addWeeks(const Poco::Timestamp& time,
                                    int64_t amount);
        ///< Add weeks to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addMonths(const Poco::LocalDateTime& time,
                                         int64_t amount);
        ///< Add days to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addMonths(const Poco::DateTime& time,
                                    int64_t amount);
        ///< Add days to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addMonths(const Poco::Timestamp& time,
                                     int64_t amount);
        ///< Add years to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime addYears(const Poco::LocalDateTime& time,
                                        int64_t amount);
        ///< Add years to a Poco::LocalDateTime.
        ///< Amount values can be positive or negative.

    static Poco::DateTime addYears(const Poco::DateTime& time,
                                   int64_t amount);
        ///< Add years to a Poco::DateTime.
        ///< Amount values can be positive or negative.

    static Poco::Timestamp addYears(const Poco::Timestamp& time,
                                    int64_t amount);
        ///< Add years to a Poco::Timestamp.
        ///< Amount values can be positive or negative.

    static Poco::LocalDateTime round(const Poco::LocalDateTime& localDateTime,
                                     const Poco::Timespan& timespan);
        ///< Rounds a Poco::LocalDateTime based on a given Poco::Timespan.
    
    static Poco::LocalDateTime ceiling(const Poco::LocalDateTime& localDateTime,
                                       const Poco::Timespan& timespan);
        ///< Rounds a Poco::LocalDateTime up based on a given Poco::Timespan.

    static Poco::LocalDateTime floor(const Poco::LocalDateTime& localDateTime,
                                     const Poco::Timespan& timespan);
        ///< Rounds a Poco::LocalDateTime down based on a given Poco::Timespan.

    static Poco::DateTime round(const Poco::DateTime& dateTime,
                                const Poco::Timespan& timespan);
        ///< Rounds a Poco::DateTime based on a given Poco::Timespan.

    static Poco::DateTime ceiling(const Poco::DateTime& dateTime,
                                  const Poco::Timespan& timespan);
        ///< Rounds a Poco::DateTime up based on a given Poco::Timespan.

    static Poco::DateTime floor(const Poco::DateTime& dateTime,
                                const Poco::Timespan& timespan);
        ///< Rounds a Poco::DateTime down based on a given Poco::Timespan.

    static Poco::Timestamp round(const Poco::Timestamp& timestamp,
                                 const Poco::Timespan& timespan);
        ///< Rounds a Poco::Timestamp based on a given Poco::Timespan.

    static Poco::Timestamp ceiling(const Poco::Timestamp& timestamp,
                                   const Poco::Timespan& timespan);
        ///< Rounds a Poco::Timestamp up based on a given Poco::Timespan.

    static Poco::Timestamp floor(const Poco::Timestamp& timestamp,
                                 const Poco::Timespan& timespan);
        ///< Rounds a Poco::Timestamp down based on a given Poco::Timespan.

    static Poco::LocalDateTime round(const Poco::LocalDateTime& localDateTime,
                                     Period::Field field);
        ///< Rounds a Poco::LocalDateTime based on a given DateTimeField.

    static Poco::LocalDateTime ceiling(const Poco::LocalDateTime& localDateTime,
                                       Period::Field field);
        ///< Rounds a Poco::LocalDateTime up based on a given DateTimeField.

    static Poco::LocalDateTime floor(const Poco::LocalDateTime& localDateTime,
                                     Period::Field field);
        ///< Rounds a Poco::LocalDateTime down based on a given DateTimeField.

    static Poco::DateTime round(const Poco::DateTime& dateTime,
                                Period::Field field);
        ///< Rounds a Poco::DateTime based on a given DateTimeField.

    static Poco::DateTime ceiling(const Poco::DateTime& dateTime,
                                  Period::Field field);
        ///< Rounds a Poco::DateTime up based on a given DateTimeField.

    static Poco::DateTime floor(const Poco::DateTime& dateTime,
                                Period::Field field);
        ///< Rounds a Poco::DateTime down based on a given DateTimeField.

    static Poco::Timestamp round(const Poco::Timestamp& timestamp,
                                 Period::Field field);
        ///< Rounds a Poco::Timestamp based on a given DateTimeField.

    static Poco::Timestamp ceiling(const Poco::Timestamp& timestamp,
                                   Period::Field field);
        ///< Rounds a Poco::Timestamp up based on a given DateTimeField.

    static Poco::Timestamp floor(const Poco::Timestamp& timestamp,
                                 Period::Field field);
        ///< Rounds a Poco::Timestamp down based on a given DateTimeField.

    static int countLeapDaysBetweenYears(int64_t startYear, int64_t endYear);
        ///< Counts the number of leap days between two years.
        ///< The start year must be greater than the end year.

    static int countLeapDaysBeforeYear(int64_t year);
        ///< Counts the number of leap days since year 0 (zero).


    static std::string format(const Poco::Timestamp& timestamp,
                              const std::string& fmt = Poco::DateTimeFormat::RFC1123_FORMAT,
                              int timeZoneDifferential = Poco::DateTimeFormatter::UTC);
        ///< Formats a given Poco::Timestamp as a string.
        ///< This is a simple wrapper for Poco::DateTimeFormatter::format().

    static std::string format(const Poco::DateTime& dateTime,
                              const std::string& fmt = Poco::DateTimeFormat::RFC1123_FORMAT,
                              int timeZoneDifferential = Poco::DateTimeFormatter::UTC);
        ///< Formats a given Poco::DateTime as a string.
        ///< This is a simple wrapper for Poco::DateTimeFormatter::format().

    static std::string format(const Poco::LocalDateTime& dateTime,
                              const std::string& fmt = Poco::DateTimeFormat::RFC1123_FORMAT);
        ///< Formats a given Poco::LocalDateTime as a string.
        ///< This is a simple wrapper for Poco::DateTimeFormatter::format().

    static std::string format(const Poco::Timespan& timespan,
                              const std::string& fmt = "%dd %H:%M:%S.%i");
        ///< Formats a given Poco::Timespan as a string.
        ///< This is a simple wrapper for Poco::DateTimeFormatter::format().

};


inline Poco::Timestamp& operator += (Poco::Timestamp& timestamp,
                                     const Period& period)
{
    timestamp = Utils::add(timestamp, period);
    return timestamp;
}


inline Poco::DateTime& operator += (Poco::DateTime& dateTime,
                                    const Period& period)
{
    dateTime = Utils::add(dateTime, period);
    return dateTime;
}


inline Poco::LocalDateTime& operator += (Poco::LocalDateTime& localDateTime,
                                         const Period& period)
{
    localDateTime = Utils::add(localDateTime, period);
    return localDateTime;
}

inline Poco::Timestamp operator + (const Poco::Timestamp& timestamp,
                                   const Period& period)
{
    return Utils::add(timestamp, period);
}


inline Poco::DateTime operator + (const Poco::DateTime& dateTime,
                                  const Period& period)
{
    return Utils::add(dateTime, period);
}


inline Poco::LocalDateTime operator + (Poco::LocalDateTime& localDateTime,
                                       const Period& period)
{
    return Utils::add(localDateTime, period);
}

    
} } // namespace ofx::Time
