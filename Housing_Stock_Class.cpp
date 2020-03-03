#include "pch.h"
#include "Housing_Stock_Class.h"
#include <iostream>
#pragma warning(disable:26495)

namespace Housing_Stock
{
	Building& Building::set(int count)
	{
		room_count = count;
		rooms = rooms->make(room_count);
		for (int i = 0; i < room_count; ++i)
			std::cin >> rooms[i];
		return *this;
	}

	int Building::get_square()
	{
		int sum = 0;
		for (int i = 0; i < room_count; ++i)
			sum += rooms[i].get_square();
		return sum;
	}

	Building* Building::make(int num)
	{
		Building* buildings = nullptr;
		try {
			buildings = new struct Building[num];
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "Memory's full" << ba.what() << std::endl;
			return nullptr;
		}
		return buildings;
	}

	std::ostream& Flat::show(std::ostream& os) const
	{
		os << "\tFlat\nAddress: " << street_name << "\nHouse's number: " << house_number
			<< "\nFlat's number: " << flat_number << std::endl;
		if (state)
			os << "State: Busy" << std::endl;
		else
			os << "State: Free" << std::endl;
		for (int i = 0; i < 4; ++i)
		{
			os << rooms[i].get_room_name() << " (" << rooms[i].get_square() << " meter squared) " << std::endl;
		}
		return os;
	}

	std::istream& Flat::get(std::istream& is)
	{
		std::cout << "Enter the house's nmbr, flat's nmbr and cost of one squared meter " << std::endl;
		state = 0;
		std::cout << "House's number --> ";
		is >> house_number;
		std::cout << "Flat's number --> ";
		is >> flat_number;
		std::cout << "Area's cost --> ";
		is >> area_cost;
		rooms = rooms->make(4);
		for (int i = 0; i < 4; ++i)
			is >> rooms[i];
		return is;
	}

	Flat::Flat(const Flat& flat)
	{
		this->area_cost = flat.area_cost;
		this->flat_number = flat.flat_number;
		this->house_number = flat.house_number;
		this->state = flat.state;
		this->street_name = flat.street_name;
		rooms = rooms->make(4);
		for (int i = 0; i < 4; ++i) {
			std::string tmp_string = flat.rooms[i].get_room_name();
			this->rooms[i].set(tmp_string, flat.rooms[i].get_square());
		}
	}

	int Flat::get_square() const
	{
		int summ = 0;
		if (rooms)
			for (int i = 0; i < 4; ++i)
			{
				summ += rooms[i].get_square();
			}
		return summ;
	}

	Flat& Flat::set(const std::string& name, int num_h, int num_f, int price)
	{
		street_name = name;
		house_number = num_h;
		flat_number = num_f;
		area_cost = price;
		rooms = rooms->make(4);
		return *this;
	}

	Flat::~Flat()
	{
		if (rooms)
		{
			delete[] rooms;
		}
	}

	std::ostream& Appartment::show(std::ostream& os) const
	{
		os << "\tApartment\nAddress: " << street_name << "\nHouse's number: " << house_number
			<< "\nFlat's number: " << flat_number << std::endl;
		if (state)
			os << "State: Busy" << std::endl;
		else
			os << "State: Free" << std::endl;
		for (int i = 0; i < rooms_count; ++i)
		{
			os << rooms[i].get_room_name() << " (" << rooms[i].get_square() << " meter squared) " << std::endl;
		}
		return os;
	}

	std::istream& Appartment::get(std::istream& is)
	{
		std::cout << "Enter the house's nmbr, flat's nmbr, room's count and cost of one squared meter" << std::endl;
		state = 0;
		std::cout << "House's number --> ";
		is >> house_number;
		std::cout << "Flat's number --> ";
		is >> flat_number;
		std::cout << "Room's count --> ";
		is >> rooms_count;
		std::cout << "Area's cost --> ";
		is >> area_cost;
		rooms = rooms->make(rooms_count);
		for (int i = 0; i < rooms_count; ++i)
			is >> rooms[i];
		return is;
	}

	Appartment::Appartment(const Appartment& aprt)
	{
		this->area_cost = aprt.area_cost;
		this->flat_number = aprt.flat_number;
		this->house_number = aprt.house_number;
		this->state = aprt.state;
		this->street_name = aprt.street_name;
		this->rooms_count = aprt.rooms_count;
		rooms = rooms->make(rooms_count);
		for (int i = 0; i < rooms_count; ++i) {
			std::string tmp_string = aprt.rooms[i].get_room_name();
			this->rooms[i].set(tmp_string, aprt.rooms[i].get_square());
		}
	}

	int Appartment::get_square() const
	{
		int summ = 0;
		for (int i = 0; i < rooms_count; ++i)
		{
			summ += rooms[i].get_square();
		}
		return summ;
	}

	Appartment::~Appartment()
	{
		if (rooms) {
			delete[] rooms;
		}
	}

	std::ostream& Cottage::show(std::ostream& os) const
	{
		os << "\tCottage\nAddress: " << street_name << "\nHouse's number: " << house_number << std::endl;
		if (state)
			os << "State: Busy" << std::endl;
		else
			os << "State: Free" << std::endl;
		for (int i = 0; i < buildings_count; ++i)
		{
			os << "Building's numbre: " << buildings[i].get_building_number() << " (room's count - " << buildings[i].get_room_count() << ") " << std::endl;
		}
		return os;
	}

	std::istream& Cottage::get(std::istream& is)
	{
		std::cout << "Enter the house's nmbr, building's count and cost of one squared meter --> " << std::endl;
		state = 0;
		std::cout << "House's number --> ";
		is >> house_number;
		std::cout << "Building's count --> ";
		is >> buildings_count;
		std::cout << "Area's cost --> ";
		is >> area_cost;
		buildings = buildings->make(buildings_count);
		for (int i = 0; i < buildings_count; ++i) {
			is >> buildings[i];
			buildings[i].set(buildings[i].get_room_count());
		}
		return is;
	}

	Cottage::Cottage(const Cottage& ctg)
	{
		this->area_cost = ctg.area_cost;
		this->house_number = ctg.house_number;
		this->state = ctg.state;
		this->street_name = ctg.street_name;
		this->buildings_count = ctg.buildings_count;
		buildings = buildings->make(buildings_count);
		for (int i = 0; i < buildings_count; ++i)
		{
			int room_count = ctg.buildings[i].get_room_count();
			buildings[i].set_bldnmbr(ctg.buildings[i].get_building_number());
			buildings[i].set_roomcnt(ctg.buildings[i].get_room_count());
			buildings[i].rooms = buildings[i].rooms->make(room_count);
			for (int j = 0; j < room_count; ++j)
			{
				std::string name = ctg.buildings[i].rooms[j].get_room_name();
				int tmp_square = ctg.buildings[i].rooms[j].get_square();
				buildings[i].rooms[j].set(name, tmp_square);
			}
		}
	}

	int Cottage::get_square() const
	{
		int summ = 0;
		for (int i = 0; i < buildings_count; ++i)
		{
			summ += buildings[i].get_square();
		}
		return summ;
	}

	Room* Room::make(int num)
	{
		Room* rooms = nullptr;
		try {
			rooms = new struct Room[num];
		}
		catch (const std::bad_alloc& ba)
		{
			std::cout << ba.what() << std::endl;
			return nullptr;
		}
		return rooms;
	}
	std::istream& operator>>(std::istream& is, Room& room)
	{
		std::cout << "Name: ";
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(is, room.room_name);
		std::cout << "Area:";
		is >> room.area;
		return is;
	}
	std::istream& operator>>(std::istream& is, Building& buildings)
	{
		std::cout << "Building's number: ";
		is >> buildings.building_number;
		std::cout << "Room's count: ";
		is >> buildings.room_count;
		return is;
	}
}