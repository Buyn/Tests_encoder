/* coment bloc  {{{
 *
 * Класс сканера поверехности ножа
 * спомошью енкодера
 * version 0.0
***************************************
***************************************
 *  }}}*/
/* include bloc {{{*/
#ifndef EnScaner_h
#define EnScaner_h
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "simplencoder.h"
#include "slavespi.h"
#include "postepmotor.h"
/*}}}*/
//define bloc  {{{
#define motorX 1
#define motorY 0
#define motorZ 3
#define X_MIN 0
#define X_MAX 1000
#define Z_MIN 0
#define Z_MAX 100
#define Y_MIDL 100
/*}}}*/
// EnScaner calss{{{
typedef void (*GeneralMessageFunction) ();
class EnScaner {
 public: // {{{
	EnScaner(SimplEncoder * , SlaveSPI * , POStepMotor * , GeneralMessageFunction );
	bool stop(void);
	bool start(void);
	bool scanScript(void);
	bool isStoping(void);
	bool motorStop(int);
	bool motorToMax(int);
	bool motorToMin(int);
	unsigned long pos, steps_from_last;
	/*}}}*/
	/* private: * {{{*/
#ifndef UNITTEST/*{{{*/
 private:
#endif /* UNITTEST }}}*/
	SimplEncoder * encoder; 
	SlaveSPI * spi; 
	POStepMotor * posm; 
	GeneralMessageFunction loopMain; 
	bool enable, stopingScaner;
	void waitloop(void);
	/*}}}*/
 };
 /*}}}*/
#endif
