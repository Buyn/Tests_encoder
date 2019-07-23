#ifdef UNITTEST
#include "gtest.h"
#include "towavestepmotor.h"
#include "postepmotor.h"
#include "Shiftin.h"
#include "shiftout.h"
#include "slavespi.h"

TEST(POStepmotor, Constaract) {/*{{{*/
	ShiftIn _shIn ;
	ShiftOut _shOt;
	SlaveSPI _spi(8);
	POStepMotor sm = POStepMotor(& _shIn, & _shOt, &  _spi);
	EXPECT_EQ(sm.size, 0);
	EXPECT_EQ(sm.shIn, &_shIn);
	EXPECT_EQ(sm.shOt, &_shOt);
	EXPECT_EQ(sm.spi, &_spi);
	}
/*}}}*/

TEST(POStepmotor, addMotor) {/*{{{*/
	ShiftIn _shIn ;
	ShiftOut _shOt;
	SlaveSPI _spi(8);
	POStepMotor sm = POStepMotor(& _shIn, & _shOt, &  _spi);
	EXPECT_EQ(sm.size, 0);
	sm.addMotor(1, 2, 3, true);
	EXPECT_EQ(sm.size, 1);
	sm.addMotor(1, 2, 3, true);
	EXPECT_EQ(sm.size, 2);
//	EXPECT_NE(sm.update_time, tmp)<<" "<<micros();
//	delay(1);
	}
/*}}}*/

TEST(POStepmotor, getMotor) {/*{{{*/
	ShiftIn _shIn ;
	ShiftOut _shOt;
	SlaveSPI _spi(8);
	POStepMotor sm = POStepMotor(& _shIn, & _shOt, &  _spi);
	EXPECT_EQ(sm.size, 0);
	sm.addMotor(1, 2, 3, true);
	EXPECT_EQ(sm.size, 1);
	sm.addMotor(4, 5, 6, false);
	EXPECT_EQ(sm.size, 2);
	EXPECT_EQ(sm.getMotor(0)->dirpin, 3);
	EXPECT_EQ(sm.getMotor(1)->dirpin, 6);
//	EXPECT_false(sm.done());
//	EXPECT_NE(sm.update_time, tmp)<<" "<<micros();
	}
/*}}}*/
TEST(ShiftIn, isOnZero) {/*{{{*/
	ShiftIn shIn ;
	shIn.bytesVal  = 16;
	//TODO могут возникнуть проблемы с лонго поскольку основное безнаковый инт
	EXPECT_EQ(shIn.isOn(0), false);
	EXPECT_EQ(shIn.isOn(4), true)<<shIn.bytesVal;
	}
/*}}}*/
TEST(ShiftOut, isOnZero) {/*{{{*/
	ShiftOut shOt ;
	shOt.oldPinValues  = 8;
	EXPECT_EQ(shOt.isOn(0), false);
	EXPECT_EQ(shOt.isOn(4), true);
	}
/*}}}*/
TEST(ShiftOut, On_Off) {/*{{{*/
	ShiftOut shOt ;
	shOt.oldPinValues  = 0;
	EXPECT_EQ( shOt.on(10), 512);//but 10 is 512, 11 is 1024
	shOt.oldPinValues  = 8;
	EXPECT_EQ( shOt.on(3), 12 );
	EXPECT_EQ(shOt.isOn(0), false);
	EXPECT_EQ(shOt.isOn(3), true);
	EXPECT_EQ(shOt.isOn(4), true);
	EXPECT_EQ( shOt.off(3), 8 );
	EXPECT_EQ(shOt.isOn(0), false);
	EXPECT_EQ(shOt.isOn(3), false);
	EXPECT_EQ(shOt.isOn(4), true);
	EXPECT_EQ( shOt.oldPinValues  , 8);
	}
/*}}}*/
TEST(POStepmotor, startMaintanse) {/*{{{*/
	ShiftIn _shIn ;
	ShiftOut _shOt;
	SlaveSPI _spi(8);
	POStepMotor sm = POStepMotor(& _shIn, & _shOt, &  _spi);
	sm.addMotor(1, 2, 3, true);
	sm.addMotor(4, 5, 6, false);
	EXPECT_EQ(sm.size, 2);
	ToWaveStepMotor * tmpSM1 = sm.getMotor(0);
	ToWaveStepMotor * tmpSM2 = sm.getMotor(1);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	EXPECT_EQ(tmpSM1->isMaintenance, false);
	sm.startManteins(0);
	EXPECT_EQ(tmpSM1->isMaintenance, true);
	sm.runtime();
	EXPECT_EQ(tmpSM1->isMaintenance, true);
	EXPECT_EQ(tmpSM1->pos, 10);
	EXPECT_EQ(tmpSM1->value, 110);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), true);
	sm.runtime();
	sm.runtime();
	sm.runtime();
	EXPECT_EQ(tmpSM1->isMaintenance, true);
	EXPECT_EQ(tmpSM1->pos, 10);
	EXPECT_EQ(tmpSM1->value, 110);
	_shIn.bytesVal  = bitSet(_shIn.bytesVal, tmpSM1->zeropin);
	sm.runtime();
	EXPECT_EQ(tmpSM1->isMaintenance, false);
	EXPECT_EQ(tmpSM1->pos, 0);
	EXPECT_EQ(tmpSM1->value, 0);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), true);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), false);
	sm.startManteins(1);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), false);
//	EXPECT_false(sm.done());
//	EXPECT_NE(sm.update_time, tmp)<<" "<<micros();
	}
/*}}}*/
TEST(POStepmotor, gotoPOS) {/*{{{*/
	ShiftIn _shIn ;
	ShiftOut _shOt;
	SlaveSPI _spi(8);
	POStepMotor sm = POStepMotor(& _shIn, & _shOt, &  _spi);
	sm.addMotor(1, 2, 3, true);
	sm.addMotor(4, 5, 6, false);
	EXPECT_EQ(sm.size, 2);
	ToWaveStepMotor * tmpSM1 = sm.getMotor(0);
	ToWaveStepMotor * tmpSM2 = sm.getMotor(1);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	sm.gotoPOS(0, 3);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	EXPECT_EQ(tmpSM1->value, 3);
	EXPECT_EQ(tmpSM1->pos, 0);
	tmpSM1->step();
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	EXPECT_EQ(tmpSM1->value, 2);
	EXPECT_EQ(tmpSM1->pos, 1);
	tmpSM1->step();
	tmpSM1->step();
	tmpSM1->step();
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	EXPECT_EQ(tmpSM1->value, 0);
	EXPECT_EQ(tmpSM1->pos, 3);
	sm.gotoPOS(0, 2);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), true);
	EXPECT_EQ(tmpSM1->value, 1);
	EXPECT_EQ(tmpSM1->pos, 3);
	tmpSM1->step();
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), true);
	EXPECT_EQ(tmpSM1->value, 0);
	EXPECT_EQ(tmpSM1->pos, 2);
	sm.gotoPOS(1, 3);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), true);
	EXPECT_EQ(tmpSM2->value, 3);
	EXPECT_EQ(tmpSM2->pos, 0);
	tmpSM2->step();
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), true);
	EXPECT_EQ(tmpSM2->value, 2);
	EXPECT_EQ(tmpSM2->pos, 1);
	tmpSM2->step();
	tmpSM2->step();
	sm.gotoPOS(1, 0);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), false);
//	sm.gotoPOS(0, 1000);
//	EXPECT_false(sm.done());
//	EXPECT_NE(sm.update_time, tmp)<<" "<<micros();
	}
/*}}}*/
TEST(POStepmotor, setDir_to_from_Zero) {/*{{{*/
	ShiftIn _shIn ;
	ShiftOut _shOt;
	SlaveSPI _spi(8);
	POStepMotor sm = POStepMotor(& _shIn, & _shOt, &  _spi);
	sm.addMotor(1, 2, 3, true);
	sm.addMotor(4, 5, 6, false);
	EXPECT_EQ(sm.size, 2);
	ToWaveStepMotor * tmpSM1 = sm.getMotor(0);
	ToWaveStepMotor * tmpSM2 = sm.getMotor(1);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	sm.setDirFromZero(tmpSM1);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	sm.setDirToZero(tmpSM1);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), true);
	sm.setDirFromZero(tmpSM1);
	EXPECT_EQ(_shOt.isOn(tmpSM1->dirpin), false);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), false);
	sm.setDirFromZero(tmpSM2);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), true);
	sm.setDirToZero(tmpSM2);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), false);
	sm.setDirFromZero(tmpSM2);
	EXPECT_EQ(_shOt.isOn(tmpSM2->dirpin), true);
//	sm.gotoPOS(0, 1000);
//	EXPECT_false(sm.done());
//	EXPECT_NE(sm.update_time, tmp)<<" "<<micros();
	}
/*}}}*/
#endif
