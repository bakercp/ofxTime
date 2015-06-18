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


#include "ofx/Time/Utils.h"
#include "Poco/Exception.h"


namespace ofx {
namespace Time {


std::vector<Poco::Timestamp> Utils::getInstances(const Poco::Timestamp& start,
                                                 std::size_t quantity,
                                                 const Period& period)
{
    std::vector<Poco::Timestamp> results;

    Poco::Timestamp t(start);

    for (std::size_t i = 0; i < quantity; ++i)
    {
        results.push_back(t);
        t = add(t, period);
    }

    return results;
}


std::vector<Poco::Timestamp> Utils::getInstances(const Poco::Timestamp& start,
                                                 const Poco::Timespan& timespan,
                                                 const Period& period)
{
    return getInstances(start,
                        start + timespan.totalMicroseconds(),
                        period);
}


std::vector<Poco::Timestamp> Utils::getInstances(const Poco::Timestamp& start,
                                                 const Poco::Timestamp& end,
                                                 const Period& period)
{
    std::vector<Poco::Timestamp> results;

    for (Poco::Timestamp t(start); t < end; t = add(t, period))
    {
        results.push_back(t);
    }

    return results;
}


std::vector<Poco::Timestamp> Utils::getInstances(const Interval& Interval,
                                                 const Period& period)
{
    return getInstances(Interval.getStart(),
                        Interval.getEnd(),
                        period);
}


Poco::Timestamp Utils::toUtcTimestamp(const Poco::LocalDateTime& localDateTime)
{
    return localDateTime.utc().timestamp();
}


Poco::DateTime Utils::toUtcDateTime(const Poco::LocalDateTime& localDateTime)
{
    return localDateTime.utc();
}


Poco::LocalDateTime Utils::add(const Poco::LocalDateTime& time,
                               const Period& period)
{
    return Poco::LocalDateTime(add(time.utc(), period));
}


Poco::DateTime Utils::add(const Poco::DateTime& timez, const Period& period)
{
    Poco::DateTime dateTime = timez;

    for (int i = (int)(Period::NUM_FIELDS - 1); i > -1; --i)
    {
        Period::Field field = (Period::Field)i;

        int64_t amount = period.get(field);

        if (0 == amount) continue;

        switch (field)
        {
            case Period::MICROSECOND:
                dateTime += Poco::Timespan(amount);
                break;
            case Period::MILLISECOND:
                dateTime += Poco::Timespan(amount * Poco::Timespan::MILLISECONDS);
                break;
            case Period::SECOND:
                dateTime += Poco::Timespan(amount * Poco::Timespan::SECONDS);
                break;
            case Period::MINUTE:
                dateTime += Poco::Timespan(amount * Poco::Timespan::MINUTES);
                break;
            case Period::HOUR:
                dateTime += Poco::Timespan(amount * Poco::Timespan::HOURS);
                break;
            case Period::DAY:
                dateTime += Poco::Timespan(amount * Poco::Timespan::DAYS);
                break;
            case Period::WEEK:
                dateTime += Poco::Timespan(amount * 7 * Poco::Timespan::DAYS);
                break;
            case Period::MONTH:
            {
                int yearsToAdd  = (dateTime.month() + amount) / 12;
                int newMonth = (dateTime.month() + amount) % 12;

                // deal with negative months
                if (newMonth < 1)
                {
                    newMonth += 12;
                    yearsToAdd--;
                }

                dateTime = addYears(dateTime, yearsToAdd);

                try
                {
                    dateTime = Poco::DateTime(dateTime.year(),
                                              newMonth,
                                              1, // remove days, add back later
                                              dateTime.minute(),
                                              dateTime.second(),
                                              dateTime.millisecond(),
                                              dateTime.microsecond());
                }
                catch (Poco::Exception& exception)
                {
                    ofLogError("Utils::add()") << exception.displayText();
                }

                int numDaysInThisMonth = Poco::DateTime::daysOfMonth(dateTime.year(),
                                                                     dateTime.month());

                int daysToAdd = std::min(dateTime.day(), numDaysInThisMonth) - 1; // keep it in Interval

                // add days back
                dateTime = addDays(dateTime, daysToAdd);
                break;
            }
            case Period::YEAR:
            {
                if (amount > 0)
                {
                    int leapDays = countLeapDaysBetweenYears(dateTime.year(), dateTime.year() + amount + 1);
                    dateTime += Poco::Timespan((Poco::Timestamp::TimeDiff)(365 * amount + leapDays) * Poco::Timespan::DAYS);
                }
                else
                {
                    int leapDays = countLeapDaysBetweenYears(dateTime.year() + amount, dateTime.year() + 1);
                    dateTime -= Poco::Timespan((Poco::Timestamp::TimeDiff)(365 * -amount + leapDays) * Poco::Timespan::DAYS);
                }
                break;
            }
            default:
                ofLogWarning("Utils::add()") << "Unknown field: " << field;
        }
    }

    return dateTime;
}


Poco::Timestamp Utils::add(const Poco::Timestamp& time,
                           const Period& period)
{
    return add(Poco::DateTime(time), period).timestamp();
}


Poco::LocalDateTime Utils::addMicroseconds(const Poco::LocalDateTime& time,
                                           int64_t amount)
{
    return add(time, Period(Period::MICROSECOND, amount));
}


Poco::DateTime Utils::addMicroseconds(const Poco::DateTime& time,
                                      int64_t amount)
{
    return add(time, Period(Period::MICROSECOND, amount));
}


Poco::Timestamp Utils::addMicroseconds(const Poco::Timestamp& time,
                                       int64_t amount)
{
    return add(time, Period(Period::MICROSECOND, amount));
}


Poco::LocalDateTime Utils::addMilliseconds(const Poco::LocalDateTime& time,
                                           int64_t amount)
{
    return add(time, Period(Period::MILLISECOND, amount));
}


Poco::DateTime Utils::addMilliseconds(const Poco::DateTime& time,
                                      int64_t amount)
{
    return add(time, Period(Period::MILLISECOND, amount));
}


Poco::Timestamp Utils::addMilliseconds(const Poco::Timestamp& time,
                                       int64_t amount)
{
    return add(time, Period(Period::MILLISECOND, amount));
}


Poco::LocalDateTime Utils::addSeconds(const Poco::LocalDateTime& time,
                                      int64_t amount)
{
    return add(time, Period(Period::SECOND, amount));
}


Poco::DateTime Utils::addSeconds(const Poco::DateTime& time,
                                 int64_t amount)
{
    return add(time, Period(Period::SECOND, amount));
}


Poco::Timestamp Utils::addSeconds(const Poco::Timestamp& time,
                                  int64_t amount)
{
    return add(time, Period(Period::SECOND, amount));
}


Poco::LocalDateTime Utils::addMinutes(const Poco::LocalDateTime& time,
                                      int64_t amount)
{
    return add(time, Period(Period::SECOND, amount));
}


Poco::DateTime Utils::addMinutes(const Poco::DateTime& time,
                                 int64_t amount)
{
    return add(time, Period(Period::SECOND, amount));
}


Poco::Timestamp Utils::addMinutes(const Poco::Timestamp& time,
                                  int64_t amount)
{
    return add(time, Period(Period::SECOND, amount));
}


Poco::LocalDateTime Utils::addHours(const Poco::LocalDateTime& time,
                                    int64_t amount)
{
    return add(time, Period(Period::HOUR, amount));
}


Poco::DateTime Utils::addHours(const Poco::DateTime& time,
                               int64_t amount)
{
    return add(time, Period(Period::HOUR, amount));
}


Poco::Timestamp Utils::addHours(const Poco::Timestamp& time,
                                int64_t amount)
{
    return add(time, Period(Period::HOUR, amount));
}


Poco::LocalDateTime Utils::addDays(const Poco::LocalDateTime& time,
                                   int64_t amount)
{
    return add(time, Period(Period::DAY, amount));
}


Poco::DateTime Utils::addDays(const Poco::DateTime& time,
                              int64_t amount)
{
    return add(time, Period(Period::DAY, amount));
}


Poco::Timestamp Utils::addDays(const Poco::Timestamp& time,
                               int64_t amount)
{
    return add(time, Period(Period::DAY, amount));
}


Poco::LocalDateTime Utils::addWeeks(const Poco::LocalDateTime& time,
                                    int64_t amount)
{
    return add(time, Period(Period::WEEK, amount));
}


Poco::DateTime Utils::addWeeks(const Poco::DateTime& time,
                               int64_t amount)
{
    return add(time, Period(Period::WEEK, amount));
}


Poco::Timestamp Utils::addWeeks(const Poco::Timestamp& time,
                                int64_t amount)
{
    return add(time, Period(Period::WEEK, amount));
}


Poco::LocalDateTime Utils::addMonths(const Poco::LocalDateTime& time,
                                     int64_t amount)
{
    return add(time, Period(Period::MONTH, amount));
}


Poco::DateTime Utils::addMonths(const Poco::DateTime& time,
                                int64_t amount)
{
    return add(time, Period(Period::MONTH, amount));
}


Poco::Timestamp Utils::addMonths(const Poco::Timestamp& time,
                                 int64_t amount)
{
    return add(time, Period(Period::MONTH, amount));
}


Poco::LocalDateTime Utils::addYears(const Poco::LocalDateTime& time,
                                    int64_t amount)
{
    return add(time, Period(Period::YEAR, amount));
}


Poco::DateTime Utils::addYears(const Poco::DateTime& time,
                               int64_t amount)
{
    return add(time, Period(Period::YEAR, amount));
}


Poco::Timestamp Utils::addYears(const Poco::Timestamp& time,
                                int64_t amount)
{
    return add(time, Period(Period::YEAR, amount));
}


Poco::LocalDateTime Utils::round(const Poco::LocalDateTime& localDateTime,
                                 const Poco::Timespan& timespan)
{
    // we convert to a raw timestamp (not to UTC) in order to roundin the local time zone
    return Poco::LocalDateTime(round(localDateTime.timestamp(), timespan) - ((Poco::Timestamp::TimeDiff)localDateTime.tzd()) * Poco::Timespan::SECONDS);
}


Poco::LocalDateTime Utils::ceiling(const Poco::LocalDateTime& localDateTime,
                                   const Poco::Timespan& timespan)
{
    // we convert to a raw timestamp (not to UTC) in order to roundin the local time zone
    return Poco::LocalDateTime(ceiling(localDateTime.timestamp(), timespan) - ((Poco::Timestamp::TimeDiff)localDateTime.tzd()) * Poco::Timespan::SECONDS);
}


Poco::LocalDateTime Utils::floor(const Poco::LocalDateTime& localDateTime,
                                 const Poco::Timespan& timespan)
{
    // we convert to a raw timestamp (not to UTC) in order to roundin the local time zone
    return Poco::LocalDateTime(floor(localDateTime.timestamp(), timespan) - ((Poco::Timestamp::TimeDiff)localDateTime.tzd()) * Poco::Timespan::SECONDS);
}


Poco::DateTime Utils::round(const Poco::DateTime& dateTime,
                            const Poco::Timespan& timespan)
{
    return round(dateTime.timestamp(), timespan);
}


Poco::DateTime Utils::ceiling(const Poco::DateTime& dateTime,
                              const Poco::Timespan& timespan)
{
    return ceiling(dateTime.timestamp(), timespan);
}


Poco::DateTime Utils::floor(const Poco::DateTime& dateTime,
                            const Poco::Timespan& timespan)
{
    return floor(dateTime.timestamp(), timespan);
}

    
Poco::Timestamp Utils::round(const Poco::Timestamp& timestamp,
                             const Poco::Timespan& timespan)
{
    Poco::Timestamp::TimeVal timeTicks = timestamp.epochMicroseconds();
    Poco::Timestamp::TimeVal spanTicks = timespan.totalMicroseconds();

    Poco::Timestamp::TimeVal ticks = ((timeTicks + (spanTicks / 2) + 1) / spanTicks);

    return ticks * spanTicks;
}


Poco::Timestamp Utils::ceiling(const Poco::Timestamp& timestamp,
                               const Poco::Timespan& timespan)
{
    Poco::Timestamp::TimeVal timeTicks = timestamp.epochMicroseconds();
    Poco::Timestamp::TimeVal spanTicks = timespan.totalMicroseconds();

    Poco::Timestamp::TimeVal ticks = (timeTicks + spanTicks - 1) / spanTicks;

    return ticks * spanTicks;
}


Poco::Timestamp Utils::floor(const Poco::Timestamp& timestamp,
                             const Poco::Timespan& timespan)
{
    Poco::Timestamp::TimeVal timeTicks = timestamp.epochMicroseconds();
    Poco::Timestamp::TimeVal spanTicks = timespan.totalMicroseconds();

    Poco::Timestamp::TimeVal ticks = (timeTicks / spanTicks);

    return ticks * spanTicks;
}


Poco::LocalDateTime Utils::round(const Poco::LocalDateTime& localDateTime,
                                 Period::Field field)
{
    // we convert to a raw timestamp (not to UTC) in order to roundin the local time zone
    return Poco::LocalDateTime(round(localDateTime.timestamp(), field) - ((Poco::Timestamp::TimeDiff)localDateTime.tzd()) * Poco::Timespan::SECONDS);
}


Poco::LocalDateTime Utils::ceiling(const Poco::LocalDateTime& localDateTime,
                                   Period::Field field)
{
    // we convert to a raw timestamp (not to UTC) in order to roundin the local time zone
    return Poco::LocalDateTime(ceiling(localDateTime.timestamp(), field) - ((Poco::Timestamp::TimeDiff)localDateTime.tzd()) * Poco::Timespan::SECONDS);
}


Poco::LocalDateTime Utils::floor(const Poco::LocalDateTime& localDateTime,
                                 Period::Field field)
{
    // we convert to a raw timestamp (not to UTC) in order to roundin the local time zone
    return Poco::LocalDateTime(floor(localDateTime.timestamp(), field) - ((Poco::Timestamp::TimeDiff)localDateTime.tzd()) * Poco::Timespan::SECONDS);
}


Poco::DateTime Utils::round(const Poco::DateTime& dateTime,
                            Period::Field field)
{
    switch(field)
    {
        case Period::MICROSECOND:
            return round(dateTime, 1);
        case Period::MILLISECOND:
            return round(dateTime, Poco::Timespan::MILLISECONDS);
        case Period::SECOND:
            return round(dateTime, Poco::Timespan::SECONDS);
        case Period::MINUTE:
            return round(dateTime, Poco::Timespan::MINUTES);
        case Period::HOUR:
            return round(dateTime, Poco::Timespan::HOURS);
        case Period::DAY:
            return round(dateTime, Poco::Timespan::DAYS);
        case Period::WEEK:
            return round(dateTime, Poco::Timespan::DAYS * 7);
        case Period::MONTH:
            return round(dateTime, Poco::Timespan::DAYS * 365.25 / 12);
        case Period::YEAR:
            return round(dateTime, Poco::Timespan::DAYS * 365.25);
        default:
            ofLogWarning("Utils::round()") << "Unknown field: " << field;
            return dateTime;
    }
}

Poco::DateTime Utils::ceiling(const Poco::DateTime& dateTime,
                              Period::Field field)
{
    switch(field)
    {
        case Period::MICROSECOND:
            return ceiling(dateTime, 1);
        case Period::MILLISECOND:
            return ceiling(dateTime, Poco::Timespan::MILLISECONDS);
        case Period::SECOND:
            return ceiling(dateTime, Poco::Timespan::SECONDS);
        case Period::MINUTE:
            return ceiling(dateTime, Poco::Timespan::MINUTES);
        case Period::HOUR:
            return ceiling(dateTime, Poco::Timespan::HOURS);
        case Period::DAY:
            return ceiling(dateTime, Poco::Timespan::DAYS);
        case Period::WEEK:
            return ceiling(dateTime, Poco::Timespan::DAYS * 7);
        case Period::MONTH:
            return ceiling(dateTime, Poco::Timespan::DAYS * 365.25 / 12);
        case Period::YEAR:
            return ceiling(dateTime, Poco::Timespan::DAYS * 365.25);
        default:
            ofLogWarning("Utils::round()") << "Unknown field: " << field;
            return dateTime;
    }
}

Poco::DateTime Utils::floor(const Poco::DateTime& dateTime,
                            Period::Field field)
{
    switch(field)
    {
        case Period::MICROSECOND:
            return floor(dateTime, 1);
        case Period::MILLISECOND:
            return floor(dateTime, Poco::Timespan::MILLISECONDS);
        case Period::SECOND:
            return floor(dateTime, Poco::Timespan::SECONDS);
        case Period::MINUTE:
            return floor(dateTime, Poco::Timespan::MINUTES);
        case Period::HOUR:
            return floor(dateTime, Poco::Timespan::HOURS);
        case Period::DAY:
            return floor(dateTime, Poco::Timespan::DAYS);
        case Period::WEEK:
            return floor(dateTime, Poco::Timespan::DAYS * 7);
        case Period::MONTH:
            return floor(dateTime, Poco::Timespan::DAYS * 365.25 / 12);
        case Period::YEAR:
            return floor(dateTime, Poco::Timespan::DAYS * 365.25);
        default:
            ofLogWarning("Utils::round()") << "Unknown field: " << field;
            return dateTime;
    }
}

Poco::Timestamp Utils::round(const Poco::Timestamp& timestamp,
                             Period::Field field)
{
    return round(Poco::DateTime(timestamp), field).timestamp();
}


Poco::Timestamp Utils::ceiling(const Poco::Timestamp& timestamp,
                               Period::Field field)
{
    return ceiling(Poco::DateTime(timestamp), field).timestamp();
}


Poco::Timestamp Utils::floor(const Poco::Timestamp& timestamp,
                             Period::Field field)
{
    return floor(Poco::DateTime(timestamp), field).timestamp();
}


int Utils::countLeapDaysBetweenYears(int64_t startYear, int64_t endYear)
{
    // http://stackoverflow.com/questions/4587513/how-to-calculate-number-of-leap-years-between-two-years-in-c-sharp

    if (startYear > endYear)
    {
        std::swap(startYear, endYear);
        ofLogWarning("Math::countLeapYearsBetween()") << "Start year was larger than end year, swapping.";
    }

    return countLeapDaysBeforeYear(endYear) - countLeapDaysBeforeYear(startYear + 1);
}


int Utils::countLeapDaysBeforeYear(int64_t year)
{
    // http://stackoverflow.com/questions/4587513/how-to-calculate-number-of-leap-years-between-two-years-in-c-sharp
    if (year < 1)
    {
        year = 1;
        ofLogWarning("Math::countLeapYearsBefore()") << "Year was < 1, setting year = 1";
    }

    year--;

    return (year / 4) - (year / 100) + (year / 400);
}


std::string Utils::format(const Poco::Timestamp& timestamp,
                          const std::string& fmt,
                          int timeZoneDifferential)
{
    return Poco::DateTimeFormatter::format(timestamp,
                                           fmt,
                                           timeZoneDifferential);
}

std::string Utils::format(const Poco::DateTime& dateTime,
                          const std::string& fmt,
                          int timeZoneDifferential)
{
    return Poco::DateTimeFormatter::format(dateTime,
                                           fmt,
                                           timeZoneDifferential);
}

std::string Utils::format(const Poco::LocalDateTime& dateTime,
                          const std::string& fmt)
{
    return Poco::DateTimeFormatter::format(dateTime, fmt);
}

std::string Utils::format(const Poco::Timespan& timespan,
                          const std::string& fmt)
{
    return Poco::DateTimeFormatter::format(timespan, fmt);
}



} } // namespace ofx::Time
