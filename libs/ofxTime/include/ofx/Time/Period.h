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


#include <vector>
#include <cstdlib>
#include <stdint.h>
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"


namespace ofx {
namespace Time {


class Period
    // A Period represents an abstract amount of time.  In some cases a concrete
    // number of microseconds can be calculated (e.g. for DateTimeFields such
    // as MICROSECOND, MILLISECOND, SECOND, MINUTE, HOUR), but for some measures
    // of time (e.g. HOUR, DAY, WEEK, MONTH, YEAR), it is only possible to
    // calculate the equivalent number of microseconds relative to a known
    // calendar start time.  This is because concepts such as "MONTH" and "YEAR"
    // are vary due to "leap" seconds, and other calendrical irregularities.
    //
    // Empty or NULL periods are those that have all fields set to zero.
{
public:
    enum Field
        /// Symbolic names of Poco::DateTime fields for manipulating dates.
    {
        MICROSECOND = 0,///< The microsecond field.
        MILLISECOND,    ///< The millisecond field.
        SECOND,         ///< The second field.
        MINUTE,         ///< The minute field.
        HOUR,           ///< The hour field.
        DAY,            ///< The day field.
        WEEK,           ///< The week increment field.
        MONTH,          ///< The month field
        YEAR            ///< The year field.
    };

    enum 
    {
        NUM_FIELDS = YEAR + 1
    };

    Period();
        ///< Create a 0 period.

    Period(Field field, int64_t amount);
        ///< Create a period with a given amount in a given field.
        ///< The amount can be negative.

    virtual ~Period();
        ///< Destroy the Period.

    void set(Field field, int64_t amount);
        ///< Set the value of a specific field.

    Poco::Timestamp::TimeVal get(Field field) const;
        ///< Get the given field's amount.

    void add(Field field, int64_t amount);
        ///< Add the given amount to the given Field.
        ///< The amount can be negative.

    void addMicroseconds(int64_t amount);
        ///< Add microseconds.
        ///< The amount can be negative.

    void addMilliseconds(int64_t amount);
        ///< Add milliseconds.
        ///< The amount can be negative.

    void addSeconds(int64_t amount);
        ///< Add seconds.
        ///< The amount can be negative.

    void addMinutes(int64_t amount);
        ///< Add minutes.
        ///< The amount can be negative.

    void addHours(int64_t amount);
        ///< Add hours.
        ///< The amount can be negative.

    void addDays(int64_t amount);
        ///< Add days.
        ///< The amount can be negative.

    void addWeeks(int64_t amount);
        ///< Add weeks.
        ///< The amount can be negative.

    void addMonths(int64_t amount);
        ///< Add months.
        ///< The amount can be negative.

    void addYears(int64_t amount);
        ///< Add years.
        ///< The amount can be negative.

    void clear(Field field);
        ///< Clear a given Field's value.

    bool empty() const;
        ///< Returns true iff all possible fields are set to 0.

    Period  operator +  (const Period& period) const;
	Period  operator -  (const Period& period) const;
	Period& operator += (const Period& period);
	Period& operator -= (const Period& period);

    static Period Microsecond();
        ///< Returns a period of one microsecond.

    static Period Microseconds(int64_t amount);
        ///< Returns a period of microseconds.
        ///< The amount can be negative.

    static Period Millisecond();
        ///< Returns a period of one millisecond.

    static Period Milliseconds(int64_t amount);
        ///< Returns a period of milliseconds.
        ///< The amount can be negative.

    static Period Second();
        ///< Returns a period of one second.

    static Period Seconds(int64_t amount);
        ///< Returns a period of seconds.
        ///< The amount can be negative.

    static Period Minute();
        ///< Returns a period of one minute.

    static Period Minutes(int64_t amount);
        ///< Returns a period of minutes.
        ///< The amount can be negative.

    static Period Hour();
        ///< Returns a period of one hour.

    static Period Hours(int64_t amount);
        ///< Returns a period of hours.
        ///< The amount can be negative.

    static Period Day();
        ///< Returns a period of one day.

    static Period Days(int64_t amount);
        ///< Returns a period of days.
        ///< The amount can be negative.

    static Period Week();
        ///< Returns a period of one week.

    static Period Weeks(int64_t amount);
        ///< Returns a period of days.
        ///< The amount can be negative.

    static Period Month();
        ///< Returns a period of one month.

    static Period Month(int64_t amount);
        ///< Returns a period of months.
        ///< The amount can be negative.

    static Period Year();
        ///< Returns a period of one year.

    static Period Years(int64_t amount);
        ///< Returns a period of years.
        ///< The amount can be negative.

private:
    typedef std::vector<int64_t> FieldMap;

    FieldMap _fields;

};



} } // namespace ofx::Time
