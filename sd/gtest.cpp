#ifdef UNITTEST
#include "gtest.h"
#include "stepmotor.h"
#include "la.h"


TEST(LA, init) {
	LA la = LA(2);
	EXPECT_EQ(PRINTLINE, 5000);
	EXPECT_FALSE(la.have_data());
	}

TEST(LA, get_text) {
	LA la = LA(2);
	la.micarr[0] = 10000;
	la.micarr[1] = 10100;
	la.micarr[2] = 16000;
	la.micarr[3] = 16500;
	la.micarr[4] = 17000;
	la.boolarr[0] = true;
	la.boolarr[1] = false;
	la.boolarr[2] = true;
	la.boolarr[3] = false;
	la.boolarr[4] = true;
	la.boolarr[5] = false;
	la.index = 4;
	std::cerr << la.micarr[0]<< std::endl;
	char ctest[10000] ;
	String stest = la.reset_counter();
	std::cerr << stest.c_str()<< std::endl;
	stest += String(la.micarr[0]);
	std::cerr << stest.c_str()<< std::endl;
//	stest = la.reset_counter();
//	stest.toCharArray(ctest, 10000);
////	stest += "Fuck";
//	std::cerr << stest<< std::endl;
//	std::cerr << stest.c_str()<< std::endl;
//	std::cerr << ctest<< std::endl;
//	stest.toCharArray(ctest, 100);
//	std::cerr << stest<< std::endl;
//	std::cerr << ctest<< std::endl;
//	EXPECT_STREQ(ctest, "1") <<" = "<<stest;
	}

TEST(stepmotor, setspeed) {
	StepMotor sm = StepMotor(2);
	EXPECT_EQ(sm.timeout, START_TIME_OUT);
	sm.set_speed(1);
	EXPECT_EQ(sm.timeout, 1);
	}

TEST(stepmotor, resetimer) {
	StepMotor sm = StepMotor(2);
	unsigned long tmp = sm.update_time;
	EXPECT_EQ(sm.update_time, tmp);
	sm.resetimer();
	EXPECT_NE(sm.update_time, tmp);
	}

TEST(stepmotor, runtime) {
	StepMotor sm = StepMotor(2);
	sm.set_speed(2);
	unsigned long tmp = sm.update_time;
	sm.move(10);
	EXPECT_EQ(sm.value, 10);
	EXPECT_EQ(sm.update_time, tmp);
	sm.runtime();
	EXPECT_EQ(sm.update_time, tmp);
	EXPECT_EQ(sm.value, 10);
	delay(1);
	sm.runtime();
	EXPECT_NE(sm.update_time, tmp)<<" "<<micros();
	delay(1);
	EXPECT_EQ(sm.value, 9)<<" "<<micros();
	delay(1);
	sm.set_speed(0);
	sm.resetimer();
	tmp = sm.update_time;
	EXPECT_EQ(sm.update_time, tmp)<<" "<<micros();
	EXPECT_EQ(sm.value, 9)<<" "<<micros();
	sm.runtime();
	EXPECT_NE(sm.update_time, tmp);
	EXPECT_EQ(sm.value, 8);
	}

TEST(stepmotor, Done) {
	StepMotor sm = StepMotor(2);
	sm.set_speed(2);
	sm.move(3);
	EXPECT_EQ(sm.value, 3);
	sm.step();
	sm.step();
	EXPECT_FALSE(sm.done());
	EXPECT_EQ(sm.value, 1);
	sm.step();
	EXPECT_EQ(sm.value, 0);
	EXPECT_TRUE(sm.done());
	EXPECT_EQ(sm.value, 0);
	EXPECT_FALSE(sm.done());
	EXPECT_EQ(sm.value, 0);
	sm.move(1);
	EXPECT_EQ(sm.value, 1);
	EXPECT_FALSE(sm.done());
	sm.step();
	EXPECT_EQ(sm.value, 0);
	EXPECT_TRUE(sm.done());
	EXPECT_EQ(sm.value, 0);
	EXPECT_FALSE(sm.done());
	EXPECT_EQ(sm.value, 0);
//	EXPECT_NE(sm.update_time, tmp)<<" "<<micros();
	}

TEST(stepmotor, Stop) {
	StepMotor sm = StepMotor(2);
	sm.move(10);
	EXPECT_EQ(sm.value, 10);
	sm.step();
	EXPECT_EQ(sm.value, 9);
	sm.stop(100);
	EXPECT_EQ(sm.value, 100);
	sm.stop();
	EXPECT_EQ(sm.value, 0);
	sm.step();
	EXPECT_EQ(sm.value, 0);
	sm.step();
	EXPECT_EQ(sm.value, 0);
	}

#endif
