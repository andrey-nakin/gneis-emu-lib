#include <gtest/gtest.h>

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <isnp/util/FileNameBuilderMessenger.hh>

int main(int argc, char* argv[]) {
	G4RunManager runManager;
	runManager.SetUserInitialization(new QGSP_INCLXX_HP);

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/random/setSeeds 12345 12345"));

	isnp::util::FileNameBuilderMessenger fileNameBuilderMessenger;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
