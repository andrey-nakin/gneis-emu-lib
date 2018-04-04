#include <gtest/gtest.h>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <Randomize.hh>

int main(int argc, char* argv[]) {
	G4RunManager runManager;
	runManager.SetUserInitialization(new QGSP_INCLXX_HP);

	G4Random::setTheSeed(12345);

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
