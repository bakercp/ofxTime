//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/Time/Period.h"


namespace ofx {
namespace Time {


Period::Period():
    _fields(FieldMap(YEAR + 1, 0))
{
}


Period::Period(Field field, int64_t amount):
    _fields(FieldMap(YEAR + 1, 0))
{
    set(field, amount);
}


Period::~Period()
{
}


void Period::set(Field field, int64_t amount)
{
    _fields[field] = amount;
}


Poco::Timestamp::TimeVal Period::get(Field field) const
{
    return _fields[field];
}


void Period::add(Field field, int64_t amount)
{
    _fields[field] += amount;
}


void Period::clear(Field field)
{
    _fields[field] = 0;
}
    

bool Period::empty() const
{
    FieldMap::const_iterator iter = _fields.begin();

    while (iter != _fields.end())
    {
        if (0 != *iter)
        {
            return false;
        }
    }

    return true;
}


Period  Period::operator +  (const Period& period) const
{
    Period _period;

    for (int field = 0; field < (int)NUM_FIELDS; ++field)
    {
        _period.set((Field)field, _fields[field] + period._fields[field]);
    }

    return _period;
}

Period  Period::operator -  (const Period& period) const
{
    Period _period;

    for (int field = 0; field < (int)NUM_FIELDS; ++field)
    {
        _period.set((Field)field, _fields[field] - period._fields[field]);
    }

    return _period;
}

Period& Period::operator += (const Period& period)
{
    for (int field = 0; field < (int)NUM_FIELDS; ++field)
    {
        _fields[field] += period._fields[field];
    }

    return *this;
}


Period& Period::operator -= (const Period& period)
{
    for (int field = 0; field < (int)NUM_FIELDS; ++field)
    {
        _fields[field] -= period._fields[field];
    }

    return *this;
}


Period Period::Microsecond()
{
    return Period(MICROSECOND, 1);
}


Period Period::Microseconds(int64_t amount)
{
    return Period(MICROSECOND, amount);
}


Period Period::Millisecond()
{
    return Period(MILLISECOND, 1);
}


Period Period::Milliseconds(int64_t amount)
{
    return Period(MILLISECOND, amount);
}
    

Period Period::Second()
{
    return Period(SECOND, 1);
}


Period Period::Seconds(int64_t amount)
{
    return Period(SECOND, amount);
}
    

Period Period::Minute()
{
    return Period(MINUTE, 1);
}


Period Period::Minutes(int64_t amount)
{
    return Period(MINUTE, amount);
}


Period Period::Hour()
{
    return Period(HOUR, 1);
}


Period Period::Hours(int64_t amount)
{
    return Period(HOUR, amount);
}


Period Period::Day()
{
    return Period(DAY, 1);
}


Period Period::Days(int64_t amount)
{
    return Period(DAY, amount);
}


Period Period::Week()
{
    return Period(WEEK, 1);
}


Period Period::Weeks(int64_t amount)
{
    return Period(WEEK, amount);
}


Period Period::Month()
{
    return Period(MONTH, 1);
}


Period Period::Month(int64_t amount)
{
    return Period(MONTH, amount);
}


Period Period::Year()
{
    return Period(YEAR, 1);
}


Period Period::Years(int64_t amount)
{
    return Period(YEAR, amount);
}


} } // namespace ofx::Time
