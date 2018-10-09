#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/facility/Beam5.hh>

namespace isnp {

namespace facility {

TEST(Beam5Messenger, SetXAngle) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility beam5"));

	auto const facility = Beam5::GetInstance();

	EXPECT_DOUBLE_EQ(-2 * deg, facility->GetXAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/xAngle -5 deg"));
	EXPECT_DOUBLE_EQ(-5 * deg, facility->GetXAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/xAngle -2 deg"));

}

TEST(Beam5Messenger, SetYAngle) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility beam5"));

	auto const facility = Beam5::GetInstance();

	EXPECT_DOUBLE_EQ(-32 * deg, facility->GetYAngle());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/facility/beam5/yAngle -25 deg"));
	EXPECT_DOUBLE_EQ(-25 * deg, facility->GetYAngle());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/facility/beam5/yAngle -32 deg"));

}

TEST(Beam5Messenger, SetVerbose) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility beam5"));

	auto const facility = Beam5::GetInstance();

	EXPECT_EQ(0, facility->GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/verbose 1"));
	EXPECT_EQ(1, facility->GetVerboseLevel());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand("/isnp/facility/beam5/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/facility/beam5/verbose 4"));
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/verbose 0"));

}

TEST(Beam5Messenger, SetC5Diameter) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility beam5"));

	auto const facility = Beam5::GetInstance();

	EXPECT_DOUBLE_EQ(100 * mm, facility->GetC5Diameter());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/facility/beam5/c5/diameter 50 mm"));
	EXPECT_DOUBLE_EQ(50 * mm, facility->GetC5Diameter());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand("/isnp/facility/beam5/c5/diameter 0 mm"));
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/facility/beam5/c5/diameter 100 mm"));

}

TEST(Beam5Messenger, SetC5Material) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility beam5"));

	auto const facility = Beam5::GetInstance();

	EXPECT_EQ("BR05C5S5", facility->GetC5Material());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/beam5/c5/material G4_BRASS"));
	EXPECT_EQ("G4_BRASS", facility->GetC5Material());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/beam5/c5/material BR05C5S5"));

}

TEST(Beam5Messenger, SetHasSpallationTarget) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility beam5"));

	auto const facility = Beam5::GetInstance();

	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/hasSpTarget 0"));
	EXPECT_FALSE(facility->GetHasSpallationTarget());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility/beam5/hasSpTarget 1"));
	EXPECT_TRUE(facility->GetHasSpallationTarget());

}

}

}
