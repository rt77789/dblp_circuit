#include <graph.h>
#include <gtest/gtest.h>


/// src/graph.cpp unit test case.
TEST(GraphTest, GraphTest1) {
	using namespace circuit;
	Network net;
	net.load("../data/graph.input");

	EXPECT_EQ(net.size_n(), 4);
	EXPECT_EQ(net.size_m(), 5);
	int node = 0;
	EXPECT_EQ(net.size_neighbor(node), 3);
	EXPECT_EQ(net.degree(node), 3);

	Edge e = net.edge(node, 0);	
	EXPECT_EQ(e.u, 0);
	EXPECT_EQ(e.v, 1);
	EXPECT_EQ(e.w1, 1);
	EXPECT_EQ(e.w2, 0);

	e = net.edge(node, 1);	
	EXPECT_EQ(e.u, 0);
	EXPECT_EQ(e.v, 2);
	EXPECT_EQ(e.w1, 1);
	EXPECT_EQ(e.w2, 0);

	e = net.edge(node, 2);	
	EXPECT_EQ(e.u, 0);
	EXPECT_EQ(e.v, 3);
	EXPECT_EQ(e.w1, 0);
	EXPECT_EQ(e.w2, 1);
}
