#include <G4VisExecutive.hh>
#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <Randomize.hh>

#include "gneis/runner/BasicRunner.hh"

gneis::runner::BasicRunner::BasicRunner() {

}

gneis::runner::BasicRunner::~BasicRunner() {

}

int gneis::runner::BasicRunner::run(int const argc, const char* const argv[],
		std::function<void(G4RunManager&)> closure) {

	G4RunManager runManager;

	G4Random::setTheEngine(new CLHEP::RanecuEngine);

	closure(runManager);

	G4VisExecutive visManager("Quiet");
	visManager.Initialize();

	auto uiManager = G4UImanager::GetUIpointer();

	if (argc > 1) {
		// first argument is a script file name
		const G4String command = "/control/execute ";
		const G4String fileName = argv[1];
		uiManager->ApplyCommand(command + fileName);
	} else {
		// no arguments passed to executable
		auto ui = new G4UIExecutive(argc, const_cast<char**>(argv));
		ui->SessionStart();
	}

	return 0;
}
