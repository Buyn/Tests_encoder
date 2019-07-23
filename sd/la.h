/* coment bloc {{{
 *
 * Protatip of encoder class in siplefaed form
 }}}*/
/* include bloc {{{*/
#ifndef laveanaliser_h
#define laveanaliser_h
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
/*}}}*/
//define bloc  {{{
#define ARRMAX 		10000
#define PRINTLINE 	5000
#define PRINTPERIOD 	1000
/*}}}*/
// Lavel analiser calss{{{
class LA {
 public: // {{{
   LA(int );
	bool have_data();
	String get_sensor_txt(unsigned long);
	String reset_counter();
	void counter();
	/*}}}*/
	#ifndef UNITTEST
 private: /*{{{*/
	#endif /* UNITTEST */	
	void set_interrupts(void);
	void reset_time();
	unsigned long sensor_time, delay_time, delta;
	unsigned int index, print_index;
	unsigned int micarr[ARRMAX];
	bool boolarr[ARRMAX];
	String temptxt;
	int pin;
	/*}}}*/
 };
 /*}}}*/
#endif
