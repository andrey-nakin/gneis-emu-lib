#include <gtest/gtest.h>

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4PhysListFactory.hh>
#include <isnp/init/InitMessengers.hh>

int main(int argc, char* argv[]) {
	G4RunManager runManager;

	G4PhysListFactory factory;

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/random/setSeeds 12345 12345"));

	isnp::init::InitMessengers initMessengers(runManager);
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
