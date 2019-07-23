#include "EnScaner.h"

/*   EnScaner::EnScaner   * {{{ */
EnScaner::EnScaner( 
						SimplEncoder * _encoder, 
						SlaveSPI * _spi, 
						POStepMotor * _posm, 
						GeneralMessageFunction _loopMain){
	encoder = _encoder; 
	spi = _spi; 
	posm = _posm; 
	loopMain = _loopMain;
	enable = false;
	stopingScaner = false;
	} //}}}

/*   EnScaner::waitloop   * {{{ */
void EnScaner::waitloop(void){
	loopMain();
	} //}}}

/*   EnScaner::start   * {{{ */
bool EnScaner::start(void){
	if (enable || stopingScaner) return false;
	enable = true;
	scanScript();
	return true;
	} //}}}

/*   EnScaner::stop   * {{{ */
bool EnScaner::stop(void){
	enable = false;
	stopingScaner = true;
	//set x to 0
	return true;
	} //}}}

/*   EnScaner::isStoping   * {{{ */
bool EnScaner::isStoping(void){
	if (enable) ruturn false;
	//set x to 0
	//if pos x ==0
	// stopingScaner = false;
	// send encoder stop
	return true;
	} //}}}

/*   EnScaner::motorStop   * {{{ */
void EnScaner::motorStop(int tag){
	posm->stop(
	} //}}}


/*   EnScaner::scanScript   * {{{ */
bool EnScaner::scanScript(void){
	return true;
	} //}}}

/*   EnScaner::stop   * {{{ */
void EnScaner::stop(void){
	//value = 0;
	} //}}}



