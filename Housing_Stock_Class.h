#pragma once
#pragma warning(disable:26495)

#ifndef HOUSING_STOCK_CLASS_H
#define HOUSING_STOCK_CLASS_H

#include <iostream>
#include <string>

namespace Housing_Stock
{
	struct Room
	{
	private:
		std::string room_name;
		int area;
	public:
		Room() { area = 0; room_name = ""; }
		Room& set(std::string& name, int sqr) { room_name = name; area = sqr; return *this; }
		Room& set(const std::string& name, int sqr) { room_name = name; area = sqr; return *this; }
		int get_square() { return area; }
		std::string get_room_name() { return room_name; }
		Room* make(int num);
		friend std::istream& operator>>(std::istream& is, Room& room);
	};

	struct Building
	{
	private:
		int building_number;
		int room_count;
	public:
		Room* rooms;
		Building() :building_number(0), room_count(0), rooms(nullptr) {}
		Building& set(int count);
		int get_square();
		Building& set_roomcnt(int a) { room_count = a; return *this; }
		Building& set_bldnmbr(int a) {
			building_number = a; return *this;
		}
		int get_building_number() { return building_number; }
		int get_room_count() { return room_count; }
		Building* make(int num);
		~Building() { delete[] rooms; }
		friend std::istream& operator>>(std::istream& is, Building& buildings);
	};

	class Home
	{
	protected:
		virtual std::ostream& show(std::ostream&) const = 0;
		virtual std::istream& get(std::istream&) = 0;
	public:
		virtual Home* clone() const = 0;
		friend std::ostream& operator<<(std::ostream& os, const Home& H) { return H.show(os); }
		friend std::istream& operator>>(std::istream& is, Home& H) { return H.get(is); }
		virtual int IAm()const = 0;
		virtual int get_square() const = 0;
		virtual int get_state() = 0;
		virtual int get_price() = 0;
		virtual std::string get_street_name() = 0;
		virtual void set_state(int) = 0;
		virtual void set_address(std::string) = 0;
		virtual ~Home() {};
	};

	class Flat : public Home
	{
	private:
		std::string street_name;
		int house_number;
		int flat_number;
		int state;
		int area_cost;
	protected:
		virtual std::ostream& show(std::ostream&) const override;
		virtual std::istream& get(std::istream&) override;
	public:
		Room* rooms;
		Flat() : house_number(0), flat_number(0), state(0), area_cost(0), rooms(nullptr), street_name("") {}
		Flat& set(const std::string& name, int num_h, int num_f, int price);
		Flat(const Flat&);
		virtual Flat* clone() const override { return new Flat(*this); }
		virtual int IAm()const { return 1; }
		virtual int get_square() const override;
		virtual int get_state() override { return state; }
		virtual int get_price() override { return area_cost; }
		virtual std::string get_street_name() override { return street_name; }
		virtual void set_state(int st) override { state = st; }
		virtual void set_address(std::string name) { street_name = name; }
		virtual ~Flat();
	};

	class Appartment : public Home
	{
	private:
		std::string street_name;
		int house_number;
		int flat_number;
		int rooms_count;
		int state;
		int area_cost;
	protected:
		virtual std::ostream& show(std::ostream&) const override;
		virtual std::istream& get(std::istream&) override;
	public:
		Room* rooms;
		Appartment() : house_number(0), flat_number(0), rooms_count(1) {}
		Appartment(const Appartment& aprt);
		virtual Appartment* clone() const override { return new Appartment(*this); }
		virtual int IAm()const { return 2; }
		virtual int get_square() const override;
		virtual int get_state() override { return state; }
		virtual int get_price() override { return area_cost; }
		virtual std::string get_street_name() override { return street_name; }
		virtual void set_state(int st) override { state = st; }
		virtual void set_address(std::string name) { street_name = name; }
		virtual ~Appartment();
	};

	class Cottage : public Home
	{
	private:
		std::string street_name;
		int house_number;
		int buildings_count;
		int state;
		int area_cost;
	protected:
		virtual std::ostream& show(std::ostream&) const override;
		virtual std::istream& get(std::istream&) override;
	public:
		Building* buildings;
		Cottage() : house_number(0), buildings_count(1) {}
		Cottage(const Cottage& ctg);
		virtual Cottage* clone() const override { return new Cottage(*this); }
		virtual int IAm()const { return 3; }
		virtual int get_square() const override;
		virtual int get_state() override { return state; }
		virtual int get_price() override { return area_cost; }
		virtual std::string get_street_name() override { return street_name; }
		virtual void set_state(int st) override { state = st; }
		virtual void set_address(std::string name) { street_name = name; }
		virtual ~Cottage() { if (this->buildings) delete[] buildings; }
	};
}
#endif // !HOUSING_STOCK_CLASS_H
