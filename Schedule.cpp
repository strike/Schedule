/*
	schedule.cpp - Schedule Library
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

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "Arduino.h"
#include "Schedule.h"
#include <inttypes.h>
#include <avr/pgmspace.h>

/******************************************************************************
 * Definitions
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/

Schedule::Schedule(schedule_type t, const char **s){
	schTable = s;
	type = t;
}

/******************************************************************************
 * User API
 ******************************************************************************/

bool Schedule::check(uint8_t month, uint8_t hour){
	if ((month < 1) or (month > 12) or (hour < 0) or (hour > 24)){
		return false;
	}

	switch(type){
		case MONTH:
			if ((hour >= pgm_read_byte(pgm_read_word(&(schTable[month-1])))) and 
					( hour <  pgm_read_byte(pgm_read_word(&(schTable[month-1]))+1))){
				return true;
			} 
			break;

		case SEASON:
			uint8_t season;
			switch(month){
				case 12:
				case 1:
				case 2:
					season = 0; break;
				case 3:
				case 4:
				case 5:
					season = 1; break;
				case 6:
				case 7:
				case 8:
					season = 2; break;
				case 9:
				case 10:
				case 11:
					season = 3; break;
				default:
					season = 4;
			}

			if ((hour >= pgm_read_byte(pgm_read_word(&(schTable[season])))) and 
					( hour <  pgm_read_byte(pgm_read_word(&(schTable[season]))+1))){
				return true;
			} 
			break;	

		default:
			Serial.println(F("SCHEDULE ERROR: Bad type"));
			break;
	}

	return false;  
}

bool Schedule::check(uint8_t month, uint8_t day, uint8_t hour){
	if ((month < 1) or (month > 12) or (day < 1) or (day > 31) or (hour < 0) or (hour > 24)){
		return false;
	}

	uint8_t last = 0, val, cur, i = 0;

	switch(type){
		case MONTH:
		case SEASON:
			return(Schedule::check(month, hour));
			break;
		case INTERVAL:
			while (pgm_read_word(&(schTable[last])) != 0){last++;}

			// finding interval
			switch(last){
				case 0:
					Serial.println(F("SCHEDULE ERROR: No elements"));
					return false;
				case 1:
					cur = pgm_read_word(&(schTable[0])); // not tested
					break;
				default:
					for (int i = 0; i < last; ++i){
						val = pgm_read_word(&(schTable[i]));
						if ( ((pgm_read_byte(val)) > month) or
								 (( (pgm_read_byte(val)) == month) and (pgm_read_byte(val+1) > day) )){
							if (i == 0){
								cur = pgm_read_word(&(schTable[last-1])); break;
							} else {
								cur = pgm_read_word(&(schTable[i-1])); 
								break;
							}
						} else if ( ((pgm_read_byte(val)) == month) and (pgm_read_byte(val+1) == day) ){
							cur = val; break;
						}
						cur = val;
					}
					break;
			}

			// 
			if ((hour >= pgm_read_byte(cur+2)) and 
					( hour <  pgm_read_byte(cur+3))) {
				return true;
			} 
			break;

		default:
			Serial.println(F("SCHEDULE ERROR: No elements"));
			break;
	}

	return false;  
}
