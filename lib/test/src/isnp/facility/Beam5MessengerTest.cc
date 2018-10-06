#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/facility/Beam5.hh>

namespace isnp {

namespace facility {

TEST(Beam5Messenger, SetXAngle) {

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(-2 * deg, facility.GetXAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/xAngle -5 deg"));
	EXPECT_DOUBLE_EQ(-5 * deg, facility.GetXAngle());

}

TEST(Beam5Messenger, SetYAngle) {

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(-32 * deg, facility.GetYAngle());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/facility/beam5/yAngle -25 deg"));
	EXPECT_DOUBLE_EQ(-25 * deg, facility.GetYAngle());

}

TEST(Beam5Messenger, SetVerbose) {

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, facility.GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/verbose 1"));
	EXPECT_EQ(1, facility.GetVerboseLevel());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand("/isnp/facility/beam5/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/facility/beam5/verbose 4"));

}

TEST(Beam5Messenger, SetC5Diameter) {

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(100 * mm, facility.GetC5Diameter());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/facility/beam5/c5/diameter 50 mm"));
	EXPECT_DOUBLE_EQ(50 * mm, facility.GetC5Diameter());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand("/isnp/facility/beam5/c5/diameter 0 mm"));

}

TEST(Beam5Messenger, SetC5Material) {

	Beam5 facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ("BR05C5S5", facility.GetC5Material());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/beam5/c5/material G4_BRASS"));
	EXPECT_EQ("G4_BRASS", facility.GetC5Material());

}

}

}
