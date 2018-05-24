#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/facility/BasicSpallation.hh>

namespace isnp {

namespace facility {

constexpr G4double GET_CURRENT_DOUBLE_VALUE_DELTA = 1.e-6;

TEST(BasicSpallationMessenger, GetHorizontalAngle)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(30 * deg, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/horizontalAngle"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetHorizontalAngle(25 * deg);
	EXPECT_NEAR(25 * deg, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/horizontalAngle"), GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetHorizontalAngle)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(30 * deg, facility.GetHorizontalAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/horizontalAngle 25 deg"));
	EXPECT_DOUBLE_EQ(25 * deg, facility.GetHorizontalAngle());

}

TEST(BasicSpallationMessenger, GetVerticalAngle)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(0 * deg, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/verticalAngle"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetVerticalAngle(10 * deg);
	EXPECT_NEAR(10 * deg, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/verticalAngle"), GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetVerticalAngle)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(0 * deg, facility.GetVerticalAngle());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/verticalAngle 10 deg"));
	EXPECT_DOUBLE_EQ(10 * deg, facility.GetVerticalAngle());

}

TEST(BasicSpallationMessenger, GetDistance)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(1 * m, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/distance"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDistance(10 * m);
	EXPECT_NEAR(10 * m, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/distance"), GET_CURRENT_DOUBLE_VALUE_DELTA);

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

TEST(BasicSpallationMessenger, GetDetectorWidth)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(10 * cm, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/detectorWidth"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDetectorWidth(20 * cm);
	EXPECT_NEAR(20 * cm, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/detectorWidth"), GET_CURRENT_DOUBLE_VALUE_DELTA);

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

TEST(BasicSpallationMessenger, GetDetectorHeight)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(10 * cm, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/detectorHeight"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDetectorHeight(20 * cm);
	EXPECT_NEAR(20 * cm, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/detectorHeight"), GET_CURRENT_DOUBLE_VALUE_DELTA);

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

TEST(BasicSpallationMessenger, GetDetectorLength)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(1 * cm, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/detectorLength"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDetectorLength(2 * cm);
	EXPECT_NEAR(2 * cm, uiManager->GetCurrentDoubleValue("/isnp/basicSpallation/detectorLength"), GET_CURRENT_DOUBLE_VALUE_DELTA);

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

TEST(BasicSpallationMessenger, GetVerboseLevel)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, uiManager->GetCurrentIntValue("/isnp/basicSpallation/verbose"));
	facility.SetVerboseLevel(1);
	EXPECT_EQ(1, uiManager->GetCurrentIntValue("/isnp/basicSpallation/verbose"));

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

TEST(BasicSpallationMessenger, GetWorldMaterial)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(G4String("G4_Galactic"), uiManager->GetCurrentStringValue("/isnp/basicSpallation/worldMaterial"));
	facility.SetWorldMaterial("G4_AIR");
	EXPECT_EQ(G4String("G4_AIR"), uiManager->GetCurrentStringValue("/isnp/basicSpallation/worldMaterial"));

}

TEST(BasicSpallationMessenger, SetWorldMaterial)
{

	BasicSpallation facility(nullptr);
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(G4String("G4_Galactic"), facility.GetWorldMaterial());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/worldMaterial G4_AIR"));
	EXPECT_EQ(G4String("G4_AIR"), facility.GetWorldMaterial());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/basicSpallation/worldMaterial invalid_material_name"));
	EXPECT_EQ(G4String("G4_AIR"), facility.GetWorldMaterial());
	EXPECT_EQ(400, uiManager->ApplyCommand("/isnp/basicSpallation/worldMaterial"));

}

}

}
