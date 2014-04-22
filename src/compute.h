
#ifndef __CIRCUIT_COMPUTE_H_EOAIX
#define __CIRCUIT_COMPUTE_H_EOAIX

#include "graph.h"
#include <set>
#include <vector>

namespace circuit {
	void calInfluenceSingle(std::vector<int>& src, const char* ofile);
	void demo();
	void init(const char* data, const char* lamfile, int threads);
	InfluenceNetwork __inet;
}
#endif
