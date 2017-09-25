#ifndef SELECTION_LIST_UTILS_H
#define SELECTION_LIST_UTILS_H 

#include "Item.h"
#include <vector>
#include <string>

using namespace std;
using namespace fingolfin::items;

namespace fingolfin
{
	class SelectionListUtils
	{
		public:
			static int get_selected_item(vector<string> const &);
	};
}
#endif
