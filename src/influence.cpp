#include "influence.h"
#include <map>
#include <cassert>
#include <cmath>

namespace circuit {
#define DEBUG
#define eps 1e-8

	InfluenceNetwork::InfluenceNetwork(const char* file, double lam = 0.25):_lam(lam) {
		load(file);
	}

	InfluenceNetwork::InfluenceNetwork(double lam = 0.25):_lam(lam) {
	}


	InfluenceNetwork::~InfluenceNetwork() {
	}

	void InfluenceNetwork::calPoten(std::vector<double>& poten) const {
		poten.resize(_net.size_n(), 0);
		
		int iterNum = 60;
		Edge e;

		for(int i = 0; i < iterNum; ++i) {
			for(int j = 0; j < _net.size_n(); ++j) {
				double fluence = 0;
				for(int k = 0; k < _net.size_neighbor(j); ++k) {
					e = _net.edge(j, k);
					fluence += e.w1 * poten[e.v];	
				}

				poten[j] = (1 + fluence) / ( 1 + _lam);
			}
		}
		/// poten[*] is the calculated potentials.
	}
	
	void InfluenceNetwork::calSinglePoten(int node, std::set<int>& s, std::vector<double>& poten) const {
		poten.resize(_net.size_n(), 0);

		std::vector<int> apart_s;
		for(int i = 0; i < _net.size_n(); ++i) {
			if(s.find(i) == s.end()) {
				apart_s.push_back(i);
			}
		}

		int iterNum = 60;
		Edge e;
		for(int i = 0; i < iterNum; ++i) {
			for(size_t j = 0; j < apart_s.size(); ++j) {
				int id = apart_s[j];

				/// 计算id的影响力.
				double fluence = 0;
				for(int k = 0; k < _net.size_neighbor(id); ++k) {
					e = _net.edge(id, k);
					fluence += e.w2 * poten[e.v];	
				}

				poten[id] = (1. / (1. + _lam)) * ((id == node ? 1 : 0) + fluence);
			}
		}

		for(int i = 0; i < _net.size_n(); ++i) {
			assert(fabs(poten[node]) > eps); /// poten[node] can't be 0.
			poten[i] *= 1. / poten[node];
		}
		/// poten[*] is the final answer.
	}

	void InfluenceNetwork::calSeedSet(int num, std::set<int>& seeds) const {
		std::vector<double> fi(_net.size_n(), 0);
		std::vector<double> fmax(_net.size_n(), 0);
		std::vector<double> fs(_net.size_n(), 0);

		std::vector<double> poten;
		calPoten(poten);

		typedef std::pair<double, int> PotenNode;


		//priority_queue<PotenNode> queue;
		typedef std::map<double, int, std::greater<double> > Queue;
		Queue queue;
		Queue::iterator iter;

		for(size_t i = 0; i < poten.size(); ++i) {
			poten[i] *= (1. + _lam);
			queue.insert(PotenNode(poten[i], i));
		}

		seeds.clear();
		int candidate = 0;

		while(seeds.size() < num) {
			fi.clear();
			iter = queue.begin();

			candidate = iter->second;

			calSinglePoten(iter->second, seeds, fi);

			double pmax = 0;
			for(int i = 0; i < _net.size_n(); ++i) {
				pmax += fi[i] * (1 - fs[i]);
			}
#ifdef DEBUG
			std::cout << "pmax: " << pmax  << " seeds.size(): " << seeds.size() << std::endl;
#endif
			queue.erase(iter);
			queue.insert(PotenNode(pmax, iter->second));

			bool flag = false;
			while(!flag) {
				for(iter = queue.begin(); iter != queue.end(); ++iter) {
					if(iter->first > pmax) {
						calSinglePoten(iter->second, seeds, fi);
						double tpmax = 0;
						for(int i = 0; i < _net.size_n(); ++i) {
							tpmax += fi[i] * (1 - fs[i]);
						}
						//// cout << ;
#ifdef DEBUG
						std::cout << "node: " << iter->second << " ,tpmax: " << tpmax << " ,pmax: " << pmax << std::endl;
#endif
						if(tpmax > pmax) {
							pmax = tpmax;
							fmax.assign(fi.begin(), fi.end());
							candidate = iter->second;				
						}
						queue.insert(PotenNode(tpmax, iter->second));
						queue.erase(iter);
					}
					else {
						flag = true;
						break;
					}
				}
			}
			seeds.insert(candidate);

			for(int i = 0; i < _net.size_n(); ++i) {
				fs[i] = 1 - (1 - fs[i]) * (1 - fmax[i]);
			}
			// cout
#ifdef DEBUG
			std::cout << "select node: " << candidate << std::endl;
#endif
			iter = queue.find(pmax);
			if(iter != queue.end())
			queue.erase(iter);
		}
	}

	void InfluenceNetwork::load(const char* file) {
		_net.load(file);
	}
	
	void InfluenceNetwork::calExpectedPoten(std::vector<double>& ep) {
		std::vector<double> poten;
		std::set<int> seeds;

		ep.resize(_net.size_n(), 0);

		for(int i = 0; i < _net.size_n(); ++i) {
			calSinglePoten(i, seeds, poten);
			ep[i] = 0;
			for(size_t j = 0; j < poten.size(); ++j) {
				ep[i] += poten[j];
			}

			std::cout << "node: " << i << " , expected potential: " << ep[i] << std::endl;
		}
	}
}
