#include "Bag.h"
#include <exception>

using namespace fingolfin::items;

Bag::Bag(int weight_limit) : _weight_limit(weight_limit), _weight(0), _items(vector<Item const *>())
{
}

Bag::~Bag()
{
	for (vector<Item const *>::iterator it = _items.begin(); it != _items.end(); ++it)
	{
		delete *it;
	}

	_items.clear();
}

int Bag::weight() const
{
	return _weight;
}

vector<Item const *> const & Bag::items() const
{
	return _items;
}

void Bag::put(Item const * item)
{
	if ((_weight + item->weight()) > _weight_limit)
	{
		throw 2;
	}

	_items.push_back(item);
	_weight += item->weight();
}

Item const * Bag::take(int index)
{
	if (index >= _items.size())
	{
		throw 1;
	}

	Item const * tmp = _items[index];
	vector<Item const *>::iterator it = _items.begin();
	for (int i = 0; i < index && it != _items.end(); i++, ++it);

	if (it != _items.end())
	{
		_items.erase(it);
	}

	_weight -= tmp->weight();

	return tmp;
}
