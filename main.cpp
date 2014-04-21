
#include <iostream>
#include <string>
#include <graph.h>
#include <influence.h>
#include <cstdio>
#include <algorithm>
#include <helper.h>
#include <cstring>

typedef std::pair<double, int> Pair;

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
		std::vector<Pair> authors;

		circuit::InfluenceNetwork inet(args[2], args[3]);
		std::vector<double> tpoten;
		inet.calInfluence(tpoten);
		authors.resize(tpoten.size());

		for(size_t i = 0; i < tpoten.size(); ++i) {
			authors[i] = Pair(tpoten[i], i);
		}
		sort(authors.begin(), authors.end(), std::greater<Pair>());

		/// TOP_K authors bounds are computed.
		const int top_k = 20;
		std::set<int> seeds;

		for(int ai = 0; ai < top_k; ++ai) {

			int node = authors[ai].second;//48299;//49550;//53154; //43902; //48299;//43902; //48299;
			std::vector<double> poten;
			//std::cout << "degree: " << inet.degree(node) << std::endl;
			inet.calSinglePoten(node, seeds, poten);

			double epsum = 0;
			for(size_t i = 0; i < poten.size(); ++i) {
				if(inet.lambda(i) > 0)
					epsum += poten[i];
			}
			std::cerr << "ai: " << ai << std::endl;
			std::cout << node << " " << epsum << " " << inet.degree(node) << std::endl;
		}
	}
	else if(strcmp(args[1], "--all-node-influence") == 0) {

		std::vector<Pair> poten;

		circuit::InfluenceNetwork inet(args[2], args[3]);
		std::vector<double> tpoten;
		inet.calInfluence(tpoten);
		poten.resize(tpoten.size());
		for(size_t i = 0; i < tpoten.size(); ++i) {
			poten[i] = Pair(tpoten[i], i);
		}
		sort(poten.begin(), poten.end(), std::greater<Pair>());

		for(size_t i = 0 ; i < poten.size(); ++i) {
			std::cout << poten[i].second << " " << poten[i].first << " " << inet.degree(poten[i].second) <<  std::endl;
		}
	}
	else if(strcmp(args[1], "--cal-linked-zones") == 0) {
		circuit::Helper helper;
		std::cout << "linked_zones number: " << helper.cal_linked_zones(args[2]) << std::endl;
	}
	else if(strcmp(args[1], "--cal-src-to-tar") == 0) {
		std::vector<double> poten;

		std::set<int> src, tar;
		tar.insert(48299); //jiawei han
		tar.insert(343718);//Peixiang Zhao	343718
		tar.insert(53438); //Xiaolei Li	53438
		tar.insert(53951); //Dong Xin	53951

		src.insert(53436); //Hector Gonzalez	53436
		src.insert(48299); //jiawei han
		src.insert(53438); //Xiaolei Li	53438
		//tar.insert(522594); // yizhou sun
		//src.insert(43901); //Charu C. Aggarwal	43901
		//src.insert(53007); //Haixun Wang	53007

		//tar.insert(137243); // Yi Zheng
		//tar.insert(118072); // Enhong Chen

		circuit::InfluenceNetwork inet(args[2], args[3]);
		double ep = inet.calSet2SetPoten(src, tar, poten, "sum");
		std::cout << "Total Influence from src to tar is: " << ep << std::endl;

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
