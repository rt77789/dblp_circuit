
#include "graph.h"

#include <fstream>
#include <cassert>
#include <map>
#include <algorithm>

namespace circuit {

	Network::Network():_n(0), _m(0) {
		//_degree.
	}

	Network::~Network() {
		_degree.clear();
		_index.clear();
		_edges.clear();
	}

	void Network::load(const char* file) {
		std::ifstream in(file);
		assert(in.is_open());

		assert(in >> _n >> _m);

		int u = 0, v = 0;
		double w1 = 0, w2 = 0;

		_edges.resize(_m);
		_degree.resize(_n);

//		double max_w = 0;

		for(int i = 0; i < _m; ++i) {
			in >> _edges[i].u >> _edges[i].v >> _edges[i].w1 >> _edges[i].w2;
			//std::cout << _edges[i].w1 << " " << _edges[i].w2 << std::endl;
			//assert(_edges[i].w1 <= 1 + 1e-8 && _edges[i].w2 <= 1 + 1e-8);
//			max_w = max_w > _edges[i].w1 ? max_w : _edges[i].w1;
//			max_w = max_w > _edges[i].w2 ? max_w : _edges[i].w2;

			_edges[i].c1 = _edges[i].c2 = 1;
			_degree[_edges[i].u]++;
		}
//		std::cout << "max_w: " << max_w << std::endl;

		sort(_edges.begin(), _edges.end());

		int m1 = 0;
		for(int i = 0; i < _m; ++i) {
			if(_edges[i].u != _edges[m1].u || _edges[i].v != _edges[m1].v) {
				_edges[++m1] = _edges[i];
			}
			else {
				++_edges[m1].c1;
			}
		}

		if(_m) {
			_m = m1 + 1;
		}

		_index.resize(_n, 0);

		for(int i = 0; i < _m; ++i) {
			_index[_edges[i].u] = i;
		}

		for(int i = 1; i < _n; ++i) {
			if(_index[i] < _index[i-1]) {
				_index[i] = _index[i-1];
			}
		}

		in.close();
	}

	int Network::size_n() const {
		return _n;
	}

	int Network::size_m() const {
		return _m;
	}

	int Network::degree(int node) const {
		return _degree[node];
	}

	int Network::size_neighbor(int node) const {
		return node == 0 ? _index[node] + 1 : _index[node] - _index[node-1];
	}

	Edge Network::edge(int node, int idx) const {
		return node == 0 ? _edges[idx] : _edges[_index[node-1] + 1 + idx];
	}
};
