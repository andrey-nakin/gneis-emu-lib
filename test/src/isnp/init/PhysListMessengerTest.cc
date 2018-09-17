#include <gtest/gtest.h>
#include <G4UImanager.hh>
#include "isnp/init/FacilityMessenger.hh"

namespace isnp {

namespace init {

TEST(PhysListMessenger, SetPhysList)
{

	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));
	EXPECT_EQ(500, uiManager->ApplyCommand("/isnp/physList bad_pl_name"));

}

}

}
