
#include "helper.h"
#include <fstream>
#include <cassert>
#include <iostream>

namespace circuit {

	UnionSet::UnionSet(int n) {
		_rank.resize(n, 0);
		_set.resize(n, 0);
		for(int i = 0; i < n; ++i)
			_set[i] = i;
	}
	UnionSet::~UnionSet() {
	}

	int UnionSet::find_set(int node) {
		if(node == _set[node]) return node;
		_set[node] = find_set(_set[node]);
		return _set[node];
	}

	void UnionSet::link_set(int n1, int n2) {
		// check n1 and n2 are the roots.
		int r1 = find_set(n1), r2 = find_set(n2);
		if(r1 != r2) {
			if(_rank[r1] > _rank[r2]) {
				_set[r2] = r1;
			}
			else if(_rank[r1] < _rank[r2]) {
				_set[r1] = r2;
			}
			else {
				_set[r2] = r1;
				_rank[r1]++;
			}
		}
	}
	//--- UnionSet above. ---- //

	/*
	Helper::Helper() {
		
	}

	Helper::~Helper() {
	}
	*/

	int Helper::cal_linked_zones(const char* file) {
		std::ifstream in(file);
		assert(in.is_open());

		int n = 0, m = 0;
		int u = 0, v = 0;
		double w1 = 0, w2 = 0;

		assert(in >> n >> m);

		UnionSet us(n);

		for(int i = 0; i < m; ++i) {
			in >> u >> v >> w1 >> w2;

			us.link_set(u, v);
		}

		std::vector<int> count(n, 0);

		for(int i = 0; i < n; ++i) {
			int rnode = us.find_set(i);
			std::cout << "node: " << i << ", root: " << rnode << std::endl;
			++count[rnode];
		}

		int linked_zones = 0;
		int max_zone = 0;
		for(int i = 0; i < n; ++i) {
			if(count[i] > 0) {
				++linked_zones;
			}
			max_zone = max_zone > count[i] ? max_zone : count[i];
		}
	
		std::cout << "max_zone: " << max_zone << std::endl;
		
		in.close();
		return linked_zones;
	}
}
