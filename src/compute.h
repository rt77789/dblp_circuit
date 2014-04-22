
#ifndef __CIRCUIT_COMPUTE_H_EOAIX
#define __CIRCUIT_COMPUTE_H_EOAIX

#include "graph.h"
#include <set>
#include <vector>

namespace circuit {

	void calInfluenceSingle(std::vector<int>& srcs, std::vector< std::vector<int> >& tars, const char* ofile);
	void demo(const char* data, const char* lamfile, const char* va, const char* sif);
	void init(const char* data, const char* lamfile, int threads);
}
#endif
