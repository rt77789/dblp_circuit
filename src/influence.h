
#ifndef __CIRCUIT_INFLUENCE_H_EOAIX
#define __CIRCUIT_INFLUENCE_H_EOAIX

#include "graph.h"
#include <set>
#include <vector>

namespace circuit {
	class InfluenceNetwork {
		public:
			///
			InfluenceNetwork(const char* file, double lam);
			InfluenceNetwork(double lam);
			InfluenceNetwork();
			InfluenceNetwork(const char* file, const char* lamfile);

			~InfluenceNetwork();

			/**/
			void calSeedSet(int num, std::set<int>& seeds) const;
			void load(const char* file);
			void load_lamda(const char* lamfile);
			/* Calculate potential of node apart of set s. */
			void calSinglePoten(int node, std::set<int>& s, std::vector<double>& poten) const;
			// Calculate potential of node set (src) apart of set s. */
			void calSetPoten(std::set<int>& src, std::set<int>& s, std::vector<double>& poten) const;
			// Calculate potential of node set (src) to node set (tar).
			double calSet2SetPoten(std::set<int>& src, std::set<int>& tar, std::vector<double>& poten, const std::string& flag) const;

			int degree(int node);

			void calExpectedPoten(std::vector<double>& ep);
			void calPoten(std::vector<double>& poten) const;
			void calInfluence(std::vector<double>& poten) const; 

			double lambda(int node) const;

		private:
			double _lam;
			std::vector<double> _lams;
			Network _net;

			/**/
			//double calInnerInfluence(int node);
			//	double calOuterInfluence(int node);

			/* Calculate potentials of each node. */

	};
}
#endif

