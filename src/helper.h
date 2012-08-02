
#ifndef __CIRCUIT_HELPER_H_EOAIX
#define __CIRCUIT_HELPER_H_EOAIX
#include <vector>

namespace circuit {
	class UnionSet {
		public:
			UnionSet(int n);
			~UnionSet();

			int find_set(int node);
			void link_set(int n1, int n2);

		private:
			std::vector<int> _rank;
			std::vector<int> _set;
	};
	class Helper {	
		public:
			int cal_linked_zones(const char* file);
		private:
	};
}
#endif
