
#ifndef __CIRCUIT_COMPUTE_H_EOAIX
#define __CIRCUIT_COMPUTE_H_EOAIX

#include "graph.h"
#include <set>
#include <vector>

namespace circuit {

	void calInfluenceSingle(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* ofile);
	void demo(const char* data, const char* lamfile, const char* va, const char* sif);
	void init(const char* data, const char* lamfile, int threads);

	void run(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* sif);


	void *thread_cal_influence_single(void*ptr);

	void cal_shortest_path(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* ofile);
	void bfs(int src, std::vector<int>& poten);

	struct Query {
		std::vector<int> src;
		std::vector< std::vector<int> > tar;
		std::string ofile;
	};

	struct Node {
		int id;
		int dis;
		bool operator<(const Node& e) const {
			return dis < e.dis;
			//return u < e.u ? true : 
			//	u > e.u ? false :
			//	v <= e.u ? true : false;
		}
	};
}
#endif
