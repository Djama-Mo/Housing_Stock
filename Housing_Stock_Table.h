#pragma once

#ifndef HOUSING_STOCK_TABLE_H
#define HOUSING_STOCK_TABLE_H

//#include "pch.h"
#include "Housing_Stock_Class.h"
#include <string>
#include <vector>

using namespace Housing_Stock;

namespace Housing_Stock_Table
{
	class Table
	{
	private:
		std::vector<Home*> item;
	public:
		Home* find(std::string name);
		Table& add(Home* elem);
		void show();
		Table& settlement(Home* elem, int st);
		int state(int fl);
		~Table();
	};
}

#endif // !HOUSING_STOCK_TABLE_H
