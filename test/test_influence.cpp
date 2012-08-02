#include <influence.h>
#include <gtest/gtest.h>


/// src/graph.cpp unit test case.
TEST(InfluenceTest, InfluenceTest1) {
	using namespace circuit;

	InfluenceNetwork inet(0.5);

	inet.load("../data/graph.input");

	std::set<int> seeds;
	/*inet.calSeedSet(1, seeds);

	for(std::set<int>::iterator iter = seeds.begin(); iter != seeds.end(); ++iter) {
		std::cerr << *iter << std::endl;
		EXPECT_EQ(*iter, 0);
	}
	*/
}
