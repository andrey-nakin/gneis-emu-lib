#include <chrono>

#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <Randomize.hh>
#ifdef G4VIS_USE
#include <G4VisExecutive.hh>
#endif	//	G4VIS_USE

#include "gneis/runner/BasicRunner.hh"

gneis::runner::BasicRunner::BasicRunner(int argc_, char* argv_[]) :
		argc(argc_), argv(argv_) {

}

gneis::runner::BasicRunner::~BasicRunner() {

}

int gneis::runner::BasicRunner::Run(
		std::function<void(G4RunManager&)> closure) {

	G4RunManager runManager;

	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4Random::setTheSeed(SystemTime());

	auto uiManager = G4UImanager::GetUIpointer();

	if (argc > 1) {
		closure(runManager);

		// first argument is a script file name
		const G4String command = "/control/execute ";
		const G4String fileName = argv[1];
		uiManager->ApplyCommand(command + fileName);
	} else {
#ifdef	G4VIS_USE
		auto const visManager = new G4VisExecutive("Quiet");
		visManager->Initialize();

		// no arguments passed to executable - run in visual mode
		auto ui = new G4UIExecutive(argc, const_cast<char**>(argv));
		closure(runManager);
		uiManager->ApplyCommand("/run/initialize");
		uiManager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
#endif	//	G4VIS_USE
	}

	return 0;
}

long gneis::runner::BasicRunner::SystemTime() {
	using namespace std::chrono;
	auto const now = time_point_cast < milliseconds > (system_clock::now());
	auto const value = now.time_since_epoch();
	return value.count();
}
