#include "SelectionListUtils.h"
#include "Utils.h"
#include "Item.h"
#include <string>
#include <vector>

using namespace fingolfin;
using namespace fingolfin::items;
using namespace std;

int SelectionListUtils::get_selected_item(vector<string> const & options)
{
	Utils::print(options);
	int selection = 0;
	while (true) {
		try 
		{
			selection = stoi(Utils::read_input());
		}
		catch(exception e)
		{
			Utils::print("That is not a number!");
			continue;
		}
		if (selection == 0 || selection > options.size())
		{
			Utils::fast_print("That is not a valid selection");
			continue;
		}
		break;
	}
	return selection - 1;
}
