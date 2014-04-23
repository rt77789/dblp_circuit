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

#include <queue>

namespace circuit {

#define INF 100000000
	InfluenceNetwork __inet;
	Network __net;

	std::string __algo_type = "dfs";

	void cal_shortest_path(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* ofile) {
		std::vector<int> poten;
		FILE* fo = fopen(ofile, "w"); 
		assert(fo != NULL);

		for(size_t i = 0 ; i < srcs.size(); ++i) {
			bfs(srcs[i], poten);

			fprintf(fo, "%d", srcs[i]);
			for(size_t j = 0; j < tars[i].size(); ++j) {
				fprintf(fo, "\t%d:%d", tars[i][j], poten[tars[i][j]]);
				//assert(fwrite(&poten[j],sizeof(double), 1, fo) == 1);
			}
			fprintf(fo, "\n");
			//if(i == 19) break;
		}

		fclose(fo);

	}

	void bfs(int src, std::vector<int>& poten) {
		poten.clear();
		poten.resize(__net.size_n(), INF);

		std::priority_queue<Node> queue;
		Node ptr;
		ptr.id = src;
		ptr.dis = 0;
		std::vector<int> mask;
		mask.resize(__net.size_n()+1, 0);

		queue.push(ptr);
		mask[src] = 1;

		while(!queue.empty()) {
			Node ans = queue.top();
			poten[ans.id] = ans.dis;

			queue.pop();
			for(int k = 0; k < __net.size_neighbor(ans.id); ++k) {
				Edge e = __net.edge(ans.id, k);
				if(mask[e.v] == 0) {
					Node bns;
					bns.id = e.v;
					bns.dis = ans.dis + 1;
					queue.push(bns);
					mask[e.v] = 1;
				}
				//fluence += e.w2 * poten[e.v];	
			}
		}
	}

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
			//if(i == 19) break;
		}

		fclose(fo);
	}


	void init(const char* data, const char* lamfile, int threads) {
		__inet.load(data);
		//std::cout << "load lamda" << std::endl;
		__inet.load_lamda(lamfile);

		__net.load(data);
	}

	void run(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* sif) {
		int num = 1;
		std::vector<pthread_t> threads(num);
		std::vector<Query> queries(num);
		int iret[num];

		for(int i = 0; i < num; ++i) {
			//std::vector<int> src;
			//std::vector< std::vector<int> > tar;

			for(size_t j = i; j < srcs.size(); j+=num) {
				queries[i].src.push_back(srcs[j]);
				queries[i].tar.push_back(tars[j]);
			}
			char buffer[32] = {0};
			assert(sprintf(buffer, "%d", i) > 0);

			//qu.ofile = std::string(sif) + std::to_string(i);
			queries[i].ofile = std::string(sif) + std::string(buffer) + "." + __algo_type;

			std::cout << "thread " << queries[i].ofile << std::endl;

			iret[i] = pthread_create(threads.data() + i, NULL, thread_cal_influence_single, queries.data() + i);	
			assert(iret[i] == 0);
		}
		for(int i = 0; i < num; ++i) {
			pthread_join(threads[i], NULL);
		}
	}

	void *thread_cal_influence_single(void*ptr) {
		Query* ans = (Query*)ptr;
		std::cout << "in thread_cal_influence_single: thread " << ans->ofile << std::endl;
		if(__algo_type == "si") {
			calInfluenceSingle(ans->src, ans->tar, ans->ofile.c_str());
		}
		else if(__algo_type == "dfs") {
			cal_shortest_path(ans->src, ans->tar, ans->ofile.c_str());
					//std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* ofile) {
		}
		else {
		}
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

		//calInfluenceSingle(srcs, tars, sif);
		run(srcs, tars, sif);
	}
}
