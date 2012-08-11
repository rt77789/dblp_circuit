#include "util.h"
#include <cmath>

namespace circuit {
	void transform(const char* ifile, const char* ofile) {
		std::ifstream in(ifile);
		std::cout << ifile << std::endl;
		assert(in.is_open());

		typedef std::pair<int, double> TypeNode;
		typedef std::vector<TypeNode> NodeList;

		std::map<int, NodeList> neighborList;

		int n = 0, m = 0;

		//assert(in >> n >> m);

		int u = 0, v = 0;
		double weight = 0;

		n = 0;

		for(int i = 0; ; ++i) {
			if(!(in >> u >> v >> weight)) {
				break;
			}
			n = n > u ? n : u;
			n = n > v ? n : v;

			std::map<int, NodeList>::iterator iter = neighborList.find(u);
			if(iter == neighborList.end()) {
				NodeList uList;
				uList.push_back(TypeNode(v, weight));
				neighborList[u] = uList;
			}
			else {
				iter->second.push_back(TypeNode(v, weight));
			}
		}

		std::ofstream out(ofile);
		assert(out.is_open());

		m = 0;
		for(std::map<int, NodeList>::iterator iter = neighborList.begin();
				iter != neighborList.end(); ++iter) {
			for(size_t i = 0; i < iter->second.size(); ++i) {
				if(iter->second[i].first < iter->first) {
					/// Keep <u, v, w1, w2> unique in the output file.
					break;
				}
				++m;
			}
		}

		out << n << "\t" << m << std::endl;

		for(std::map<int, NodeList>::iterator iter = neighborList.begin();
				iter != neighborList.end(); ++iter) {
			for(size_t i = 0; i < iter->second.size(); ++i) {
				if(iter->second[i].first < iter->first) {
					/// Keep <u, v, w1, w2> unique in the output file.
					break;
				}
				out << iter->first << "\t" << iter->second[i].first << "\t";

				std::map<int, NodeList>::iterator vter = neighborList.find(v);
				double w2 = 0;

				if(vter != neighborList.end()) {
					for(size_t j = 0; j < vter->second.size(); ++j) {
						if(vter->second[j].first == u) {
							w2 = vter->second[j].second;
							break;
						}
					}
				}
				out << w2 << std::endl;
			}
		}
		out.close();
		in.close();
	}

	double sigmoid(double x) {
		return 1. / (1 + exp(-x));
	}
	double smooth(double x) {
		//return 1/(1.+0.176);
		return (x + 1) / (x + 2);
	}
}
