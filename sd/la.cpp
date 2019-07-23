#include "la.h"

/*   LA::LA   * {{{ */
LA::LA(int _pin ){
	pin = _pin;	
	delay_time	= PRINTPERIOD;
	reset_time();
	print_index = 0;
	index = 0;
	//set_interrupts();
	} //}}}
/*    LA::reset_time   {{{ */
void LA::reset_time(){ 
	sensor_time	= millis() + delay_time;
	} //}}}
/*   LA::set_interapts   * {{{ */
void LA::set_interrupts(void){
//   attachInterrupt(digitalPinToInterrupt(pin), encoder1, CHANGE );
	} //}}}

/*   LA::counter   * {{{ */
void LA::counter(void){
	if (index >= ARRMAX) return;
	index++;
	micarr[index] = micros();
	if (digitalRead(pin) == HIGH) boolarr[index] = true; 
	else boolarr[index] = false; 
	} //}}}
/*   LA::have_data   * {{{ */
bool LA::have_data(void){
  if (index  != 0 && millis() >= sensor_time) 
  		return true;
	else 
  		return false;
  } //}}}

/*   LA::reset_counter   * {{{ */
	String LA::reset_counter(void){
	temptxt = "" ;
	//temptxt = "[" + micarr[print_index]+ ":"+boolarr[print_index]+"];" + temptxt;
	temptxt += "[" ;
//temptxt =  micarr[print_index];
//temptxt += ":"; 
//temptxt +=  boolarr[print_index]; 
//temptxt += "];"; 
	print_index++;
	delta = micarr[print_index] - micarr[print_index - 1];
//while (delta < PRINTLINE && print_index < index) {
//	//temptxt = temptxt + "[" + delta  + ":" + boolarr[print_index] + "];";
//	temptxt += "[" ;
//	temptxt += delta  + ":" ;
//	temptxt += boolarr[print_index] + "];";
//	print_index++;
//	delta = micarr[print_index] - micarr[print_index - 1];
//	}
	if (print_index == index){
		print_index = 0;
		index = 0;
		reset_time();
		}
	return temptxt; 
	} //}}}
/*   LA::get_sensor_txt   * {{{ */
String LA::get_sensor_txt(unsigned long _delta){
	temptxt = temptxt + "[" + delta  + ":" + micarr[print_index - 1] + "];";
	return temptxt;
	} //}}}
