#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/facility/BasicSpallation.hh>

namespace isnp {

namespace facility {

TEST(BasicSpallationMessenger, SetHorizontalAngle)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(30 * deg, facility.GetHorizontalAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/horizontalAngle 25 deg"));
	EXPECT_DOUBLE_EQ(25 * deg, facility.GetHorizontalAngle());

}

TEST(BasicSpallationMessenger, SetVerticalAngle)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(0 * deg, facility.GetVerticalAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/verticalAngle 10 deg"));
	EXPECT_DOUBLE_EQ(10 * deg, facility.GetVerticalAngle());

}

TEST(BasicSpallationMessenger, SetDistance)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(1 * m, facility.GetDistance());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/distance 3 m"));
	EXPECT_DOUBLE_EQ(3 * m, facility.GetDistance());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/basicSpallation/distance 0 m"));

}

TEST(BasicSpallationMessenger, SetDetectorWidth)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(10 * cm, facility.GetDetectorWidth());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/detectorWidth 20 cm"));
	EXPECT_DOUBLE_EQ(20 * cm, facility.GetDetectorWidth());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/basicSpallation/detectorWidth 0 cm"));

}

TEST(BasicSpallationMessenger, SetDetectorHeight)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(10 * cm, facility.GetDetectorHeight());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/detectorHeight 20 cm"));
	EXPECT_DOUBLE_EQ(20 * cm, facility.GetDetectorHeight());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/basicSpallation/detectorHeight 0 cm"));

}

TEST(BasicSpallationMessenger, SetDetectorLength)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(1 * cm, facility.GetDetectorLength());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/detectorLength 2 cm"));
	EXPECT_DOUBLE_EQ(2 * cm, facility.GetDetectorLength());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/basicSpallation/detectorLength 0 cm"));

}

TEST(BasicSpallationMessenger, SetVerboseLevel)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, facility.GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/verbose 1"));
	EXPECT_EQ(1, facility.GetVerboseLevel());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/basicSpallation/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/basicSpallation/verbose 4"));

}

}

}
