#include "pch.h"
#include "Housing_Stock_Table.h"
#include "Housing_Stock_Class.h"
#include <iostream>
#include <string>

using namespace Housing_Stock;

namespace Housing_Stock_Table
{
	Home* Table::find(std::string tmp_street_name)
	{
		for (unsigned i = 0; i < item.size(); ++i)
			if (item[i]->get_street_name() == tmp_street_name)
				return item[i];
		return nullptr;
	}

	Table& Table::add(Home* elem)
	{
		try {
			this->item.push_back(elem->clone());
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		return *this;
	}

	void Table::show()
	{
		for (unsigned i = 0; i < item.size(); ++i)
			std::cout << *this->item[i] << std::endl << std::endl;
	}

	Table& Table::settlement(Home* elem, int st)
	{
		if (elem) {
			find(elem->get_street_name())->set_state(st);
		}
		else {
			int i = item.size() - 1;
			item[i]->set_state(st);
		}
		return *this;
	}

	int Table::state(int fl)
	{
		int a = 0;

		for (unsigned i = 0; i < item.size(); ++i)
			if (item[i]->get_state() == fl) {
				std::cout << *this->item[i] << std::endl;
				a++;
			}
		return a;
	}
	Table::~Table()
	{
		item.clear();
	}
}