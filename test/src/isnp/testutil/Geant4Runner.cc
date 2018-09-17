#include <gtest/gtest.h>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <G4UImanager.hh>

#include "isnp/testutil/Geant4Runner.hh"
#include <isnp/init/InitMessengers.hh>

void isnp::testutil::Geant4Runner::Run(std::function<void()> closure) {
	G4RunManager runManager;

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/random/setSeeds 12345 12345"));

	isnp::init::InitMessengers initMessengers(runManager);

	closure();
}
