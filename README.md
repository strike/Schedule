ABOUT
===============

schedule is arduino library for day schedule (for example, work hours). You can set interval in hours [hour on, hour off) where function would be return true and false at other time.
You can set different interval only for months, seasons and custom intervals.

USAGE
===============
Clone this library in arduino library folder (/usr/share/arduino/libraries/ (Ubuntu)) and add this code*:

For months:
--------------
```cpp
#include <Schedule.h>

prog_char jan[] PROGMEM = {3,15};
prog_char feb[] PROGMEM = {0,25}; // all day time
prog_char mar[] PROGMEM = {6,22};
prog_char apr[] PROGMEM = {7,23};
prog_char may[] PROGMEM = {7,22};
prog_char jun[] PROGMEM = {7,22};
prog_char jul[] PROGMEM = {7,22};
prog_char aug[] PROGMEM = {7,22};
prog_char sep[] PROGMEM = {11,18};
prog_char oct[] PROGMEM = {7,22};
prog_char nov[] PROGMEM = {7,22};
prog_char dec[] PROGMEM = {7,22};

PROGMEM const char *schTable[] = {jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec};

Schedule Sch(MONTH, schTable);

void checkSchedule(){
	if (Sch.check(getMonth(), getHour())){
		digitalWrite(SCHEDULE_PIN, HIGH); 
	} else {
		digitalWrite(SCHEDULE_PIN, LOW); 
	}
}

...

void loop(){
	checkSchedule();
	...
}
```

Seasons:
--------------
```cpp
#include <Schedule.h>

prog_char win[] PROGMEM = {3, 3};
prog_char spr[] PROGMEM = {5,21};
prog_char sum[] PROGMEM = {6,22};
prog_char aut[] PROGMEM = {7,23};

PROGMEM const char *schTable[] = {win, spr, sum, aut};

Schedule Sch(SEASON, schTable);

void checkSchedule(){
	if (Sch.check(getMonth(), getHour())){
		digitalWrite(SCHEDULE_PIN, HIGH); 
	} else {
		digitalWrite(SCHEDULE_PIN, LOW); 
	}
}
```


Intervals:
--------------

```cpp
#include <Schedule.h>

prog_char int1[] PROGMEM = {6, 15,	3,21}; // from 15 june to 17 september, work from 3 to 21 hour
prog_char int2[] PROGMEM = {9, 17,  4,19};
prog_char int3[] PROGMEM = {9, 18,  7,15};
prog_char int4[] PROGMEM = {10, 19,	6,23}; // from 19 october to 15 june

PROGMEM const char *schTable[] = {int1, int2, int3, int4, 0}; // 0 must be!

Schedule Sch(INTERVAL, schTable);

void checkSchedule(){
	if (Sch.check(getMonth(), getDay(), getHour())){ // day must be!
		digitalWrite(SCHEDULE_PIN, HIGH); 
	} else {
		digitalWrite(SCHEDULE_PIN, LOW); 
	}
}
```

*You are required to implement getMonth() and getHour() and maybe getDay() (for interval mode) function. For exmaple you can get datetime from GSM modem (I use SIM900) or from internet.

Check schedule:
--------------
For control chedule check I print all schedule (printAllShedule in example folder) and copy all result (from serial port) to [google table](http://goo.gl/mg8KNs) 
