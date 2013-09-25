#include <Schedule.h>

prog_char int1[] PROGMEM = {6, 15,	3,21}; // from 15 june to 17 september, work from 3 to 21 hour
prog_char int2[] PROGMEM = {9, 17,  4,19};
prog_char int3[] PROGMEM = {9, 18,  7,15};
prog_char int4[] PROGMEM = {10, 19,	6,23}; // from 19 october to 15 june

PROGMEM const char *schTable[] = {int1, int2, int3, int4, 0}; // 0 must be!

Schedule Sch(INTERVAL, schTable);

void setup() {
	Serial.begin(115200);
	delay(100);
	// month
	for(int m=1; m<13; m++){
		bool first = true;
    if (m != 1){
      Serial.println(m);
    } 
		// hour
		for(int h=-1; h<24; h++){
			if (h >= 0){
				Serial.print(h);
			} else {
				Serial.print(F("h\\m"));
			}
			Serial.print(F("\t"));
			// day
			for(int d=1; d<32; d++){
				if(first){
					Serial.print(d);
				} else {  
					Serial.print(Sch.check(m, d, h));
				}  
				Serial.print(F("\t"));
			}
			first = false;
			Serial.println("");
		}    
	} 
}

void loop(){
	delay(1);
}