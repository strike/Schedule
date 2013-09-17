/*
  schedule.h - Schedule Library
  Copyright (c) 2013 LarkIT (www.larkit.ru).  All right reserved.
  Author: Zubarev Alexander aka Strike <actionstrike@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef SCHEDULE_h
#define SCHEDULE_h

#include <inttypes.h>

enum schedule_type {
  MONTH,
  SEASON,
  INTERVAL
};

class Schedule {
  public:
    // progmem table
    Schedule(schedule_type t, const char **s);

    bool check(uint8_t month, uint8_t hour);
    bool check(uint8_t month, uint8_t day, uint8_t hour);

  private:
    // progmem month (1..12): time on (hour: 0..23), time off (hour: 0..23) or
    // progmem month (1..12): time on, time off (default), time on, time off (for 1 day), ...
    const char **schTable;
    schedule_type type;
};

#endif

