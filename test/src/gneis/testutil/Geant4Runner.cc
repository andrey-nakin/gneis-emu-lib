#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <Randomize.hh>

#include "gneis/testutil/Geant4Runner.hh"

void gneis::testutil::Geant4Runner::Run(std::function<void()> closure) {
	G4RunManager runManager;
	runManager.SetUserInitialization(new QGSP_INCLXX_HP);

	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4Random::setTheSeed(12345);

	closure();
}
