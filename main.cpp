
#include <iostream>
#include <graph.h>

int main(int argc, char** args) {

	if(argc < 2) {
		perror("Command line parameter number < 2.\n");
		return 1;
	}

	std::cout << "in root/main.cpp\n";

	circuit::Network net;
	net.load(args[1]);

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
