#include <cmath>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/generator/Spallation.hh>

namespace isnp {

namespace generator {

TEST(SpallationMessenger, SetDiameter)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(40 * mm, spallation.GetDiameter());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/diameter 50 mm"));
	EXPECT_DOUBLE_EQ(50 * mm, spallation.GetDiameter());

}

TEST(SpallationMessenger, SetVerboseLevel)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(1, spallation.GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/verbose 2"));
	EXPECT_EQ(2, spallation.GetVerboseLevel());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/spallation/gun/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/spallation/gun/verbose 4"));

}

}

}
