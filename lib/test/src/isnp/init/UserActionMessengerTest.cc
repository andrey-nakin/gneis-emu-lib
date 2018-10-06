#include <gtest/gtest.h>
#include <G4UImanager.hh>
#include "isnp/init/FacilityMessenger.hh"

namespace isnp {

namespace init {

TEST(UserActionMessenger, SetGun)
{

	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/gun spallation"));
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/gun resampling"));
	EXPECT_EQ(500, uiManager->ApplyCommand("/isnp/gun bad_name"));

}

}

}
