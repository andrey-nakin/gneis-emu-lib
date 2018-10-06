#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/facility/BasicSpallation.hh>

namespace isnp {

namespace facility {

constexpr G4double GET_CURRENT_DOUBLE_VALUE_DELTA = 1.e-6;

TEST(BasicSpallationMessenger, GetXAngle) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(-2 * deg,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/xAngle"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetXAngle(-5 * deg);
	EXPECT_NEAR(-5 * deg,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/xAngle"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetXAngle) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(-2 * deg, facility.GetXAngle());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/xAngle -5 deg"));
	EXPECT_DOUBLE_EQ(-5 * deg, facility.GetXAngle());

}

TEST(BasicSpallationMessenger, GetYAngle) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(-32 * deg,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/yAngle"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetYAngle(-10 * deg);
	EXPECT_NEAR(-10 * deg,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/yAngle"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetYAngle) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(-32 * deg, facility.GetYAngle());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/yAngle -10 deg"));
	EXPECT_DOUBLE_EQ(-10 * deg, facility.GetYAngle());

}

TEST(BasicSpallationMessenger, GetDistance) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(1 * m,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/distance"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDistance(10 * m);
	EXPECT_NEAR(10 * m,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/distance"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetDistance) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(1 * m, facility.GetDistance());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/distance 3 m"));
	EXPECT_DOUBLE_EQ(3 * m, facility.GetDistance());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/distance 0 m"));

}

TEST(BasicSpallationMessenger, GetDetectorWidth) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(10 * cm,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/detectorWidth"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDetectorWidth(20 * cm);
	EXPECT_NEAR(20 * cm,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/detectorWidth"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetDetectorWidth) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(10 * cm, facility.GetDetectorWidth());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/detectorWidth 20 cm"));
	EXPECT_DOUBLE_EQ(20 * cm, facility.GetDetectorWidth());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/detectorWidth 0 cm"));

}

TEST(BasicSpallationMessenger, GetDetectorHeight) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(10 * cm,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/detectorHeight"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDetectorHeight(20 * cm);
	EXPECT_NEAR(20 * cm,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/detectorHeight"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetDetectorHeight) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(10 * cm, facility.GetDetectorHeight());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/detectorHeight 20 cm"));
	EXPECT_DOUBLE_EQ(20 * cm, facility.GetDetectorHeight());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/detectorHeight 0 cm"));

}

TEST(BasicSpallationMessenger, GetDetectorLength) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(1 * cm,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/detectorLength"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	facility.SetDetectorLength(2 * cm);
	EXPECT_NEAR(2 * cm,
			uiManager->GetCurrentDoubleValue(
					"/isnp/facility/basicSpallation/detectorLength"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(BasicSpallationMessenger, SetDetectorLength) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(1 * cm, facility.GetDetectorLength());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/detectorLength 2 cm"));
	EXPECT_DOUBLE_EQ(2 * cm, facility.GetDetectorLength());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/detectorLength 0 cm"));

}

TEST(BasicSpallationMessenger, GetVerboseLevel) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0,
			uiManager->GetCurrentIntValue(
					"/isnp/facility/basicSpallation/verbose"));
	facility.SetVerboseLevel(1);
	EXPECT_EQ(1,
			uiManager->GetCurrentIntValue(
					"/isnp/facility/basicSpallation/verbose"));

}

TEST(BasicSpallationMessenger, SetVerboseLevel) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, facility.GetVerboseLevel());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/verbose 1"));
	EXPECT_EQ(1, facility.GetVerboseLevel());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/verbose -1"));
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/verbose 4"));

}

TEST(BasicSpallationMessenger, GetWorldMaterial) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(G4String("G4_Galactic"),
			uiManager->GetCurrentStringValue(
					"/isnp/facility/basicSpallation/worldMaterial"));
	facility.SetWorldMaterial("G4_AIR");
	EXPECT_EQ(G4String("G4_AIR"),
			uiManager->GetCurrentStringValue(
					"/isnp/facility/basicSpallation/worldMaterial"));

}

TEST(BasicSpallationMessenger, SetWorldMaterial) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(G4String("G4_Galactic"), facility.GetWorldMaterial());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/worldMaterial G4_AIR"));
	EXPECT_EQ(G4String("G4_AIR"), facility.GetWorldMaterial());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/worldMaterial invalid_material_name"));
	EXPECT_EQ(G4String("G4_AIR"), facility.GetWorldMaterial());
	EXPECT_EQ(400,
			uiManager->ApplyCommand(
					"/isnp/facility/basicSpallation/worldMaterial"));

}

}

}
