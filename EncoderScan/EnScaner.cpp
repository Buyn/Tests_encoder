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

/*   EnS caner::start   * {{{ */
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
	posm->gotoPOS(motorX, X_MIN);
	posm->gotoPOS(motorZ, Z_MIN);
	posm->gotoPOS(motorY, Y_MIDL);
	return true;
	} //}}}

/*   EnScaner::isStoping   * {{{ */
bool EnScaner::isStoping(void){
  if (enable || stopingScaner) ruturn false;
	posm->gotoPOS(motorZ, Z_MIN);
	posm->gotoPOS(motorY, Y_MIDL);
	if (posm->gotoPOS(motorX, X_MIN) == X_MIN){
		stopingScaner = false;
		//todo сообшить о завершениии екодера розбери
		return false;
		}
	return true;
	} //}}}

/*   EnScaner::motorStop   * {{{ */
void EnScaner::motorStop(int tag){
	posm->stop(tag);
	} //}}}

/*   EnScaner::scanScript   * {{{ */
bool EnScaner::scanScript(void){
	return true;
	} //}}}




