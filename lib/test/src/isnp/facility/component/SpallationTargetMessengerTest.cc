#include <gtest/gtest.h>
#include <G4UImanager.hh>
#include <isnp/facility/BasicSpallation.hh>
#include <isnp/facility/component/SpallationTarget.hh>

namespace isnp {

namespace facility {

namespace component {

TEST(BasicSpallationMessenger, SetHasCooler) {

	BasicSpallation facility;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_TRUE(static_cast<bool>(facility.GetSpallationTarget()));
	EXPECT_TRUE(facility.GetSpallationTarget()->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler false"));
	EXPECT_FALSE(facility.GetSpallationTarget()->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler true"));
	EXPECT_TRUE(facility.GetSpallationTarget()->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler 0"));
	EXPECT_FALSE(facility.GetSpallationTarget()->GetHasCooler());

	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/facility/component/spTarget/hasCooler 1"));
	EXPECT_TRUE(facility.GetSpallationTarget()->GetHasCooler());

}

}

}

}
