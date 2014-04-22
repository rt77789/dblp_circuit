#include "influence.h"
#include "compute.h"
#include "util.h"
#include <map>
#include <cassert>
#include <cmath>
#include <fstream>

namespace circuit {

	InfluenceNetwork __inet;
	void calInfluenceSingle(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* ofile) {
		std::vector<double> poten;
		std::set<int> seeds;
		FILE* fo = fopen(ofile, "w"); 
		assert(fo != NULL);

		for(size_t i = 0 ; i < srcs.size(); ++i) {
			__inet.calSinglePoten(srcs[i], seeds, poten);
			fprintf(fo, "%d", srcs[i]);
			for(size_t j = 0; j < tars[i].size(); ++j) {
				fprintf(fo, "\t%d:%lf", tars[i][j], poten[tars[i][j]]);
				//assert(fwrite(&poten[j],sizeof(double), 1, fo) == 1);
			}
			fprintf(fo, "\n");
			if(i == 4) break;
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
		int num = 0;
		std::vector<int> srcs;
		std::vector< std::vector<int> > tars;
		std::vector<int> tar;

		assert(fscanf(fin, "%d", &num) == 1);
		srcs.resize(num, 0);

		for(int i = 0; i < num; ++i) {
			int id = 0, rn = 0;
			assert(fscanf(fin, "%d", &srcs[i]) == 1);

			assert(fscanf(fin, "%d", &rn) == 1);
			tar.resize(rn, 0);

			for(int j = 0; j < rn; ++j) {
				assert(fscanf(fin, "%d", &tar[j]) == 1);
			}
			tars.push_back(tar);

			//__inet.calSinglePoten(id, seeds, poten);
		}
		fclose(fin);

		/*std::cout << srcs.size() << std::endl;
		for(size_t i = 0; i < srcs.size(); ++i) {
			std::cout << srcs[i];
			for(size_t j = 0; j < tars[i].size(); ++j) {
				std::cout << "\t" << tars[i][j];
			}
			std::cout << std::endl;
		}
		*/
		calInfluenceSingle(srcs, tars, sif);
	}
}
