
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

		typedef std::pair<int, std::string> IdAuthor;
		std::vector<IdAuthor> authors;

		authors.push_back(IdAuthor(52927, "Qiang Yang"));
		authors.push_back(IdAuthor(48299, "Jiawei Han"));
		authors.push_back(IdAuthor(49550, "Rakesh Agrawal"));
		authors.push_back(IdAuthor(53154, "Hui Xiong"));
		authors.push_back(IdAuthor(43902, "Philip S. Yu"));

		for(size_t ai = 0; ai < authors.size(); ++ai) {

			int node = authors[ai].first;//48299;//49550;//53154; //43902; //48299;//43902; //48299;
			std::vector<double> poten;
			std::cout << "degree: " << inet.degree(node) << std::endl;
			inet.calSinglePoten(node, seeds, poten);


			double epsum = 0;
			for(size_t i = 0; i < poten.size(); ++i) {
				epsum += poten[i];
			}
			std::cout << "author: " << authors[ai].second << ", node: " << node << " ,epsum: " << epsum << std::endl;
		}
	}
	else if(strcmp(args[1], "--all-node-influence") == 0) {
		circuit::InfluenceNetwork inet(args[2], args[3]);
		std::vector<double> ep;

		//inet.calExpectedPoten(ep);
		std::vector<double> poten;
		inet.calPoten(poten);
		
		//sort(poten.begin(), poten.end(), std::greater<double>());
		for(size_t i = 0 ; i < poten.size(); ++i) {
			std::cout << i << " " << poten[i] << std::endl;
		}
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
