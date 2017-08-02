#include <gtest/gtest.h>

using namespace std;

int main(int argc, char** kwargs) {
	testing::InitGoogleTest(&argc, kwargs);
	return RUN_ALL_TESTS();
}