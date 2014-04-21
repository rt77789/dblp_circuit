#include "influence.h"
#include "util.h"
#include <map>
#include <cassert>
#include <cmath>
#include <fstream>

namespace circuit {
#define DEBUG
#define EPS 1e-8

	InfluenceNetwork::InfluenceNetwork(const char* file, double lam = 0.25):_lam(lam) {
		load(file);
	}

	InfluenceNetwork::InfluenceNetwork() {
		_lam = 0.25;
	}

	InfluenceNetwork::InfluenceNetwork(double lam):_lam(lam) {
	}

	InfluenceNetwork::InfluenceNetwork(const char* file, const char* lamfile) {
		//std::cout << "load file" << std::endl;
		load(file);
		//std::cout << "load lamda" << std::endl;
		load_lamda(lamfile);
	}


	InfluenceNetwork::~InfluenceNetwork() {
	}

	void InfluenceNetwork::calInfluence(std::vector<double>& poten) const {
		calPoten(poten);
		for(int i = 0; i < _net.size_n(); ++i) {
			poten[i] /= smooth(_lams[i]);
		}
	}

	void InfluenceNetwork::calPoten(std::vector<double>& poten) const {
		poten.resize(_net.size_n(), 0);

		int iterNum = 100;
		Edge e;
		double poten_sum = 1e300;
		double threshold = 1e-3;


		for(int i = 0; i < iterNum; ++i) {
			for(int j = 0; j < _net.size_n(); ++j) {
				double fluence = 0;
				for(int k = 0; k < _net.size_neighbor(j); ++k) {
					e = _net.edge(j, k);
					fluence += e.w1 * poten[e.v];	
				}

				poten[j] = ( (_lams[j] > 0 ? 1 : 0 )+ fluence) * smooth(_lams[j]);
			}

			double tpsum = 0;
			for(size_t j = 0; j < _net.size_n(); ++j) {
				tpsum += poten[j];
			}

			if(fabs(tpsum - poten_sum) < threshold) break;
			std::cerr << "tpsum: " << tpsum << " ,poten_sum: " << poten_sum << std::endl;
			poten_sum = tpsum;
		}
		/// poten[*] is the calculated potentials.
	}

	double InfluenceNetwork::calSet2SetPoten(std::set<int>& src, std::set<int>& tar, std::vector<double>& poten) const {
		std::set<int> s;
		calSetPoten(src, s, poten);

		double ep = 0;
		for(std::set<int>::iterator iter = tar.begin(); iter != tar.end(); ++iter) {
			ep += poten[*iter];	
		}
		return ep;
	}

	void InfluenceNetwork::calSetPoten(std::set<int>& src, std::set<int>& s, std::vector<double>& poten) const {
		poten.resize(_net.size_n(), 0);

		std::vector<int> apart_s;
		for(int i = 0; i < _net.size_n(); ++i) {
			if(s.find(i) == s.end()) {
				apart_s.push_back(i);
			}
		}

		int iterNum = 100;
		Edge e;
		double poten_sum = 1e300;
		double threshold = 1e-3;

		for(int i = 0; i < iterNum; ++i) {
			std::cerr << "iter num=" << i << std::endl;

			for(size_t j = 0; j < apart_s.size(); ++j) {
				int id = apart_s[j];

				/// 计算id的影响力.
				double fluence = 0;
				for(int k = 0; k < _net.size_neighbor(id); ++k) {
					e = _net.edge(id, k);
					fluence += e.w2 * poten[e.v];	
				}

				//poten[id] = (1. / (1. + (1. / (_lams[id] + EPS)) )) * ((id == node ? 1 : 0) + fluence);
				poten[id] = smooth(_lams[id] + EPS ) * ((src.find(id) != src.end() ? 1 : 0) + fluence);
			}

			double tpsum = 0;
			for(size_t j = 0; j < _net.size_n(); ++j) {
				tpsum += poten[j];
			}
			std::cerr << "tpsum: " << tpsum << " ,poten_sum: " << poten_sum << std::endl;
			if(fabs(tpsum - poten_sum) < threshold) break;
			poten_sum = tpsum;
		}

		double max_poten = 0;
		for(std::set<int>::iterator iter = src.begin(); iter != src.end(); ++iter) {
			assert(fabs(poten[*iter]) >= EPS); /// poten[node] can't be 0.
			if(poten[*iter] > max_poten) {
				max_poten = poten[*iter];
			}
		}

		for(int i = 0; i < _net.size_n(); ++i) {
			poten[i] *= 1. / max_poten;
		}
	}
	void InfluenceNetwork::calSinglePoten(int node, std::set<int>& s, std::vector<double>& poten) const {
		poten.resize(_net.size_n(), 0);

		std::vector<int> apart_s;
		for(int i = 0; i < _net.size_n(); ++i) {
			if(s.find(i) == s.end()) {
				apart_s.push_back(i);
			}
		}

		int iterNum = 100;
		Edge e;
		double poten_sum = 1e300;
		double threshold = 1e-3;

		for(int i = 0; i < iterNum; ++i) {

			for(size_t j = 0; j < apart_s.size(); ++j) {
				int id = apart_s[j];

				/// 计算id的影响力.
				double fluence = 0;
				for(int k = 0; k < _net.size_neighbor(id); ++k) {
					e = _net.edge(id, k);
					fluence += e.w2 * poten[e.v];	
				}

				//poten[id] = (1. / (1. + (1. / (_lams[id] + EPS)) )) * ((id == node ? 1 : 0) + fluence);
				poten[id] = smooth(_lams[id] + EPS ) * ((id == node ? 1 : 0) + fluence);
			}

			double tpsum = 0;
			for(size_t j = 0; j < _net.size_n(); ++j) {
				tpsum += poten[j];
			}
			if(fabs(tpsum - poten_sum) < threshold) break;
			std::cerr << "tpsum: " << tpsum << " ,poten_sum: " << poten_sum << std::endl;
			poten_sum = tpsum;
		}

		for(int i = 0; i < _net.size_n(); ++i) {
			assert(fabs(poten[node]) >= EPS); /// poten[node] can't be 0.
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

	void InfluenceNetwork::load_lamda(const char* lamfile) {
		std::ifstream in(lamfile);

		assert(in.is_open());
		int n = 0;
		in >> n;
		_lams.resize(n, 0);

		int id = 0;
		double damping = 0;

		while(in >> id >> damping) {
			_lams[id] = damping;
		}

		in.close();
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

	int InfluenceNetwork::degree(int node) {
		return _net.degree(node);
	}

	double InfluenceNetwork::lambda(int node) const {
		return _lams[node];
	}
}

