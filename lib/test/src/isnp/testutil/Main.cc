#include <gtest/gtest.h>

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <isnp/init/InitMessengers.hh>

int main(int argc, char* argv[]) {
	G4RunManager runManager;

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/random/setSeeds 12345 12345"));

	isnp::init::InitMessengers initMessengers(runManager);
	G4cout << "ttt main" << G4endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
