#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/facility/Beam5.hh>

namespace isnp {

namespace facility {

TEST(Beam5Messenger, SetDiameter)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(100 * mm, facility.GetDiameter());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/diameter 50 mm"));
	EXPECT_DOUBLE_EQ(50 * mm, facility.GetDiameter());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/facility/beam5/diameter 0 mm"));

}

TEST(Beam5Messenger, SetAngle)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(30 * deg, facility.GetAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/angle 25 deg"));
	EXPECT_DOUBLE_EQ(25 * deg, facility.GetAngle());

}

TEST(Beam5Messenger, SetHaveCollimator1)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_FALSE(facility.GetHaveCollimator1());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/haveCollimator1 true"));
	EXPECT_TRUE(facility.GetHaveCollimator1());

}

TEST(Beam5Messenger, SetHaveCollimator2)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_FALSE(facility.GetHaveCollimator2());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/haveCollimator2 true"));
	EXPECT_TRUE(facility.GetHaveCollimator2());

}

TEST(Beam5Messenger, SetHaveCollimator3)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_FALSE(facility.GetHaveCollimator3());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/haveCollimator3 true"));
	EXPECT_TRUE(facility.GetHaveCollimator3());

}

TEST(Beam5Messenger, SetHaveCollimator4)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_FALSE(facility.GetHaveCollimator4());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/haveCollimator4 true"));
	EXPECT_TRUE(facility.GetHaveCollimator4());

}

TEST(Beam5Messenger, SetHaveCollimator5)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_TRUE(facility.GetHaveCollimator5());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/haveCollimator5 false"));
	EXPECT_FALSE(facility.GetHaveCollimator5());

}

TEST(Beam5Messenger, SetVerbose)
{

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, facility.GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/verbose 1"));
	EXPECT_EQ(1, facility.GetVerboseLevel());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/facility/beam5/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/facility/beam5/verbose 4"));

}

}

}
