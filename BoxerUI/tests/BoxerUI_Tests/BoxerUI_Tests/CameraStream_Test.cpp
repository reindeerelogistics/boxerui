// #include "pch.h"
#include "CameraStream_Test.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	EXPECT_EQ(CameraStream_Test::minorTest(2), 4);
}

//This definition will ideally be with the source files
int CameraStream_Test::minorTest(int args) {
	return args++;
}

