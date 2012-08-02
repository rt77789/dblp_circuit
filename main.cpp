
#include <iostream>
#include <string>
#include <graph.h>
#include <influence.h>
#include <cstdio>
#include <algorithm>
#include <helper.h>
#include <cstring>

int main(int argc, char** args) {

	std::string options[] = {"--single-influence", 
	"--all-node-influence", "--cal-linked-zones"};

	if(argc < 2) {
		for(int i = 0; i < 3; ++i) {
			std::cout << "\t\t" << options[i] << std::endl;
		}
		return 0;
	}

	if(strcmp(args[1], "--single-influence") == 0) {
		circuit::InfluenceNetwork inet(args[2], args[3]);


		std::set<int> seeds;

		/*
		   inet.calSeedSet(1, seeds);

		   for(std::set<int>::iterator iter = seeds.begin(); iter != seeds.end(); ++iter) {
		   std::cerr << *iter << std::endl;
		   }

		 */
		//	std::vector<double> ep;

		//	inet.calExpectedPoten(ep);
		int node = 31075;
		std::vector<double> poten;
		inet.calSinglePoten(node, seeds, poten);

		double epsum = 0;
		for(size_t i = 0; i < poten.size(); ++i) {
			epsum += poten[i];
		}
		std::cout << "node: " << node << " ,epsum: " << epsum << std::endl;


	}
	else if(strcmp(args[1], "--all-node-influence") == 0) {
	}
	else if(strcmp(args[1], "--cal-linked-zones") == 0) {
		circuit::Helper helper;
		std::cout << "linked_zones number: " << helper.cal_linked_zones(args[2]) << std::endl;
	}
	else {
	}


	//	std::cout << net.size_n() << std::endl;
	//	std::cout << net.size_m() << std::endl;
	//	int node = 0;
	//	std::cout << net.size_neighbor(node) << std::endl;
	//	std::cout << net.degree(node) << std::endl;
	//
	//	for(int i = 0; i < 
	//	
	return 0;
}
