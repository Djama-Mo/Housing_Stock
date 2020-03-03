#include "pch.h"
#include "..\hs\Housing_Stock_Class.h"
#include "..\hs\Housing_Stock_Class.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(RoomTest, InitRoom)
{
	Housing_Stock::Room rm;
	ASSERT_EQ(0, rm.get_square());
	ASSERT_EQ("", rm.get_room_name());
}

TEST(SetTest, SetRoom)
{
	Housing_Stock::Room rm;
	rm.set("Bedroom", 10);
	ASSERT_EQ(10, rm.get_square());
	ASSERT_EQ("Bedroom", rm.get_room_name());
}

TEST(SetTest, SetRoom_Com)
{
	Housing_Stock::Room rm;
	rm.set("Kitchen", 5);
	ASSERT_EQ(5, rm.get_square());
	ASSERT_EQ("Kitchen", rm.get_room_name());
}

TEST(BuildingTest, InitBuilding)
{
	Housing_Stock::Building bd;
	ASSERT_EQ(0, bd.get_building_number());
	ASSERT_EQ(0, bd.get_room_count());
	ASSERT_EQ(0, bd.get_square());
}

TEST(SetBuildingTest, SetBuilding)
{
	Housing_Stock::Building bd;
	bd.set(0);
	ASSERT_EQ(0, bd.get_building_number());
	ASSERT_EQ(0, bd.get_room_count());
	ASSERT_EQ(0, bd.get_square());
}

TEST(FlatTest, FLatConstructor)
{
	Housing_Stock::Flat fl;
	ASSERT_EQ(0, fl.get_price());
	ASSERT_EQ(0, fl.get_state());
	ASSERT_EQ(0, fl.get_square());
	ASSERT_EQ("", fl.get_street_name());
	ASSERT_EQ(1, fl.IAm());
}

TEST(FlatTest, FLatSet)
{
	Housing_Stock::Flat fl;
	fl.set("Mos", 4, 534, 2000);
	ASSERT_EQ(2000, fl.get_price());
	ASSERT_EQ(0, fl.get_state());
	ASSERT_EQ(0, fl.get_square());
	ASSERT_EQ("Mos", fl.get_street_name());
	ASSERT_EQ(1, fl.IAm());
	fl.set_state(1);
	ASSERT_EQ(1, fl.get_state());
	fl.set_address("New_add");
	ASSERT_EQ("New_add", fl.get_street_name());
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}