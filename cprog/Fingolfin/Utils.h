#ifndef UTILS_H
#define UTILS_H

#include "Item.h"
#include <string>
#include <vector>

using namespace fingolfin::items;
using namespace std;

namespace fingolfin
{
	class Utils
	{
		public:
			static int const PRINT_PAUSE; // TODO - ÖKA NÄR VI INTE TESTAR LÄNGRE

			static string read_input(void);
			static void print(string const &);
			static void print(vector<string> const &);
			static void print(vector<Item const *>);
			static void fast_print(string const &);
			static vector<string> tokenize(string const &);

			static string format(double);
	};
}

#endif
