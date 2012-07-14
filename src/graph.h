
#ifndef __CIRCUIT_NETWORK_H_EOAIX
#define __CIRCUIT_NETWORK_H_EOAIX

#include <iostream>
#include <vector>

namespace circuit {

	struct Edge {
		int u, v, c1, c2;
		double w1, w2;

		bool operator<(const Edge& e) const {
			return u < e.u ? true : 
				u > e.u ? false :
				v <= e.u ? true : false;
		}
	};

	/* Network for circuit project. */
	class Network {
		public:
			void load(const char* file);
			Network();
			~Network();

			int size_n() const;
			int size_m() const;
			int size_neighbor(int node) const;
			int degree(int node) const;

			Edge edge(int node, int idx) const;

			static void transform(const char* ifile, const char* ofile);

		private:
			int _n, _m;

			std::vector<int> _degree;
			std::vector<int> _index;
			std::vector<Edge> _edges;
	};
};

#endif
