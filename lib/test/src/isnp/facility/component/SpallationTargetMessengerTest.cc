#include <gtest/gtest.h>
#include <G4UImanager.hh>
#include <G4SystemOfUnits.hh>
#include "isnp/facility/BasicSpallation.hh"
#include "isnp/facility/component/SpallationTarget.hh"

namespace isnp {

namespace facility {

namespace component {

TEST(SpallationTargetMessenger, SetHasCooler) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility basicSpallation"));

	auto const facility = SpallationTarget::GetInstance();
	EXPECT_TRUE(facility != nullptr);

	EXPECT_TRUE(facility->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler false"));
	EXPECT_FALSE(facility->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler true"));
	EXPECT_TRUE(facility->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler 0"));
	EXPECT_FALSE(facility->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler 1"));
	EXPECT_TRUE(facility->GetHasCooler());

}

TEST(SpallationTargetMessenger, GetRotation) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility basicSpallation"));

	auto const facility = SpallationTarget::GetInstance();
	EXPECT_TRUE(facility != nullptr);

	auto const cmd = "/isnp/facility/component/spTarget/rotation";

	EXPECT_EQ(G4String("0"), uiManager->GetCurrentStringValue(cmd, 1));
	EXPECT_EQ(G4String("0"), uiManager->GetCurrentStringValue(cmd, 2));
	EXPECT_EQ(G4String("0"), uiManager->GetCurrentStringValue(cmd, 3));
	EXPECT_EQ(G4String("mrad"), uiManager->GetCurrentStringValue(cmd, 4));

	facility->SetRotation(G4ThreeVector(1., 2., 3.) * deg);
	EXPECT_EQ(G4String("1"), uiManager->GetCurrentStringValue(cmd, 1));
	EXPECT_EQ(G4String("2"), uiManager->GetCurrentStringValue(cmd, 2));
	EXPECT_EQ(G4String("3"), uiManager->GetCurrentStringValue(cmd, 3));
	EXPECT_EQ(G4String("deg"), uiManager->GetCurrentStringValue(cmd, 4));

}

}

}

}
