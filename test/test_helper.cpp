#include <helper.h>
#include <gtest/gtest.h>


/// src/graph.cpp unit test case.
TEST(HelperTest, HelperTest1) {
	using namespace circuit;
	UnionSet us(10);

	us.link_set(1, 2);
	us.link_set(2, 3);
	us.link_set(3, 4);

	EXPECT_EQ(0, us.find_set(0));
	EXPECT_EQ(1, us.find_set(1));
	EXPECT_EQ(1, us.find_set(2));
	EXPECT_EQ(1, us.find_set(3));
	EXPECT_EQ(1, us.find_set(4));

	for(int i = 5; i < 10; ++i) {
		EXPECT_EQ(i, us.find_set(i));
	}
}
