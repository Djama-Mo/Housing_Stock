#include <iostream>
#include <string>
#include "..\hs\Housing_Stock_Class.h"
#include "..\hs\Housing_Stock_Class.cpp"
#include "..\hs\Housing_Stock_Table.h"
#include "..\hs\Housing_Stock_Table.cpp"
#pragma warning(disable: 6011)

const std::string Menu[] = { "1. Add a home", "2. Find a home", "3. Show all", "4. Register the settlement",
								"5. Release of housing", "6. Show info about free homes", "7. Home options",  "0. Exit" },
	Choice = "Make your choice --> ",
	Msg = "U'r wrong, repeate pls ",
	Hm[] = { "1. Flat", "2. Apartment", "3. Cottage", "0. Exit" },
	Home_options[] = { "1. Type", "2. Info(address, state, cost)", "3. Overrall square", "0. Exit" };


const int Num = sizeof(Menu) / sizeof(Menu[0]);
const int Num_Hm = sizeof(Hm) / sizeof(Hm[0]);
const int Num_opt = sizeof(Home_options) / sizeof(Home_options[0]);

using namespace Housing_Stock;
using namespace Housing_Stock_Table;

int answer(const std::string alt[], int n);
int Add(Table&), Find(Table&), Show(Table&), Settlement(Table&), Free_homes(Table&), Busy_homes(Table&), Release(Table&), Home_option(Table&);
int(*Func[])(Table&) = { nullptr, Add, Find, Show, Settlement, Release, Free_homes, Home_option };
int getnum(const char*);

int main()
{
	Table table = { };
	int index;
	try {
		while (index = answer(Menu, Num))
			Func[index](table);
		std::cout << "That's all. Bye" << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
	return 0;
}

int Add(Table& t)
{
	int choice;
	choice = answer(Hm, Num_Hm);
	Flat flat;
	Appartment apartment;
	Cottage cottage;
	Home* tmp = nullptr;
	switch (choice)
	{
	case 1:
		tmp = &flat;
		break;
	case 2:
		tmp = &apartment;
		break;
	case 3:
		tmp = &cottage;
		break;
	case 0:
		break;
	}
	if (!choice)
		return 1;
	int fl = 0;
	std::string name;
	std::cout << "Enter the name of street to check this place --> ";
	do {
		std::cin >> name;
		if (t.find(name))
			std::cout << "This place is busy, repeat pls." << std::endl;
		else fl = 1;
	} while (fl == 0);
	tmp->set_address(name);
	std::cout << "Ok. This place's free" << std::endl;
	std::cin >> *tmp;
	Home* copyTMP(tmp);
	t.add(copyTMP);
	return 0;
}

int Find(Table& t)
{
	std::string name;
	std::cout << "Enter the name of street --> ";
	std::cin >> name;
	Home* home = t.find(name);
	if (home)
		std::cout << *home << std::endl;
	else {
		std::cout << "Not found" << std::endl;
		return 1;
	}
	return 0;
}

int Show(Table& t)
{
	t.show();
	return 0;
}

int Settlement(Table& t)
{
	int choice = 1;
	std::string name;
	std::cout << "1. New address\n2. Free home\n";
	std::cout << Choice;
	choice = getnum("");
	int a;
	switch (choice)
	{
	case 1:
		a = Add(t);
		t.settlement(nullptr, 1);
		break;
	case 2:
		std::cout << "Choose the home from this list:" << std::endl;
		if (!Free_homes(t)) {
			std::cout << "Enter the Address --> ";
			std::cin >> name;
			t.settlement(t.find(name), 1);
		}
		break;
	}
	return 0;
}

int Free_homes(Table& T)
{
	if (!T.state(0)) {
		std::cout << "Not found" << std::endl;
		return 1;
	}
	return 0;
}

int Busy_homes(Table& T)
{
	if (!T.state(1)) {
		std::cout << "Not found" << std::endl;
		return 1;
	}
	return 0;
}

int Release(Table& t)
{
	std::string name;
	std::cout << "Choose the home from this list:" << std::endl;
	if (!Busy_homes(t))
	{
		std::cout << "Enter the Address --> ";
		std::cin >> name;
		t.find(name)->set_state(0);
	}
	return 0;
}

int Home_option(Table& tab)
{
	Home* home;
	std::string name;
	int choice = Show(tab);
	std::cout << "Enter the name of street from this list --> ";
	do {
		std::cin >> name;
		home = tab.find(name);
		if (!home)
			std::cout << "Incorrect input. Repeat pls" << std::endl;
	} while (!home);
	choice = answer(Home_options, Num_opt);
	switch (choice) {
	case 1:
		switch (home->IAm())
		{
		case 1:
			std::cout << "Flat" << std::endl;
			break;
		case 2:
			std::cout << "Apartment" << std::endl;
			break;
		case 3:
			std::cout << "Cottage" << std::endl;
			break;
		}
		break;
	case 2:
		std::cout << "Stree's name: " << home->get_street_name() << std::endl;
		std::cout << "State: ";
		if (home->get_state())
			std::cout << "Busy" << std::endl;
		else
			std::cout << "Free" << std::endl;
		std::cout << "Cost of 1 squared meter: " << home->get_price() << std::endl;
		break;
	case 3:
		std::cout << "Overrall square: " << home->get_square() << std::endl;
		break;
	}
	return 0;
}

int answer(const std::string alt[], int n)
{
	int answer;
	std::string promt = Choice;
	std::cout << "\nWhat do u want to do:" << std::endl;
	for (int i = 0; i < n; ++i)
		std::cout << alt[i].c_str() << std::endl;
	do {
		std::cout << promt.c_str();
		promt = Msg;
		answer = getnum("");
	} while (answer < 0 || answer >= n);
	return answer;
}

int getnum(const char* msg)
{
	while (true) {
		std::cout << msg;
		int a;
		std::cin >> a;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Incorrect input. Try again." << std::endl;
		}
		else {
			std::cin.ignore(32767, '\n');
			return a;
		}
	}
}
