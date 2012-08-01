
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

			~InfluenceNetwork();

			/**/
			void calSeedSet(int num, std::set<int>& seeds) const;
			void load(const char* file);
			/* Calculate potential of node apart of set s. */
			void calSinglePoten(int node, std::set<int>& s, std::vector<double>& poten) const;

			void calExpectedPoten(std::vector<double>& ep);

		private:
			double _lam;
			Network _net;

			/**/
			//double calInnerInfluence(int node);
		//	double calOuterInfluence(int node);

			/* Calculate potentials of each node. */
			void calPoten(std::vector<double>& poten) const;
						
		};
}
#endif
