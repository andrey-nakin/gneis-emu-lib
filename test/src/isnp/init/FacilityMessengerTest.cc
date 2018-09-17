#include <gtest/gtest.h>
#include <G4UImanager.hh>
#include "isnp/init/FacilityMessenger.hh"

namespace isnp {

namespace init {

TEST(FacilityMessenger, SetFacility)
{

	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility beam5"));
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility basicSpallation"));
	EXPECT_EQ(500, uiManager->ApplyCommand("/isnp/facility bad_name"));

}

}

}
