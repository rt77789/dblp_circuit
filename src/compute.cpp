#include "influence.h"
#include "compute.h"
#include "util.h"
#include <map>
#include <cassert>
#include <cmath>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
			if(i == 19) break;
		}

		fclose(fo);
	}


	void init(const char* data, const char* lamfile, int threads) {
		__inet.load(data);
		//std::cout << "load lamda" << std::endl;
		__inet.load_lamda(lamfile);
	}

	void run(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* sif) {
		int num = 8;
		pthread_t threads[num];
		int iret[num];

		for(int i = 0; i < num; ++i) {
			Query qu;
			//std::vector<int> src;
			//std::vector< std::vector<int> > tar;

			for(size_t j = i; j < srcs.size(); j+=num) {
				qu.src.push_back(srcs[j]);
				qu.tar.push_back(tars[j]);
			}
			qu.ofile = std::string(sif) + std::to_string(i);
			iret[i] = pthread_create(&threads[i], NULL, thread_cal_influence_single, (void*)&qu);	
			assert(iret[i] == 0);

			pthread_join(threads[i], NULL);
		}
	}

	void *thread_cal_influence_single(void*ptr) {
		Query* ans = (Query*)ptr;
		calInfluenceSingle(ans->src, ans->tar, ans->ofile.c_str());
		pthread_exit(NULL);
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

		calInfluenceSingle(srcs, tars, sif);
	}
}
