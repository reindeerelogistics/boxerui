// #include "pch.h"
#include "CameraStream_Test.h"
#include <iostream>

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	EXPECT_EQ(CameraStream_Test::minorTest(2), 3);
}

//This definition will ideally be with the source files
int CameraStream_Test::minorTest(int args) {
std::cout<<"minor test args is now: "<<++args<<std::endl;
	return args;
}

