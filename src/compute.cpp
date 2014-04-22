#include "influence.h"
#include "compute.h"
#include "util.h"
#include <map>
#include <cassert>
#include <cmath>
#include <fstream>

namespace circuit {

	InfluenceNetwork __inet;
	void calInfluenceSingle(std::vector<int>& src, const char* ofile) {
		std::vector<double> poten;
		std::set<int> seeds;
		FILE* fo = fopen(ofile, "w"); 
		assert(fo != NULL);

		for(size_t i = 0; i < src.size(); ++i) {
			__inet.calSinglePoten(src[i], seeds, poten);
			//fprintf(fo, "%d", src[i]);
			for(size_t j = 0; j < poten.size(); ++j) {
				//fprintf(fo, "\t%lf", poten[j]);
				assert(fwrite(&poten[j],sizeof(double), 1, fo) == 1);
			}
			//fprintf(fo, "\n");
			break;
		}
		fclose(fo);
	}


	void init(const char* data, const char* lamfile, int threads) {
		__inet.load(data);
		//std::cout << "load lamda" << std::endl;
		__inet.load_lamda(lamfile);
	}

	void demo(const char* data, const char* lamfile, const char* va, const char* sif) {
		init(data, lamfile, 1);

		FILE* fin = fopen(va, "r");
		assert(fin != NULL);
		int id = 0;
		std::vector<int> src;
		while(fscanf(fin, "%d", &id) == 1) {
			src.push_back(id);	
		}
		fclose(fin);

		calInfluenceSingle(src, sif);
	}
}
