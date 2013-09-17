#include <schedule.h>

prog_char jan[] PROGMEM = {12,18};
prog_char feb[] PROGMEM = {12,18};
prog_char mar[] PROGMEM = {11,20};
prog_char apr[] PROGMEM = {11,20};
prog_char may[] PROGMEM = {9,23};
prog_char jun[] PROGMEM = {9,23};
prog_char jul[] PROGMEM = {9,23};
prog_char aug[] PROGMEM = {9,23};
prog_char sep[] PROGMEM = {9,23};
prog_char oct[] PROGMEM = {11,19};
prog_char nov[] PROGMEM = {11,19};
prog_char dec[] PROGMEM = {12,18};

PROGMEM const char *schTable[] = {jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec};
Schedule Sch(MONTH, schTable);


void setup() {
	Serial.begin(115200);
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