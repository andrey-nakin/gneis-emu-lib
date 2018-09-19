#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#ifdef G4VIS_USE
#ifndef	ISNPEMULIB_NO_VIS
#include <G4VisExecutive.hh>
#endif
#endif	//	G4VIS_USE

#include "isnp/runner/BasicRunner.hh"
#include "isnp/runner/CommandLineParser.hh"
#include "isnp/init/InitMessengers.hh"

namespace isnp {

namespace runner {

BasicRunner::BasicRunner(int argc, char* argv[]) :
		parser(std::make_unique < CommandLineParser > (argc, argv)) {

}

BasicRunner::~BasicRunner() {

}

int BasicRunner::Run(std::function<void(G4RunManager&)> closure) {

	if (parser->GetReturnCode()) {
		return parser->GetReturnCode();
	}

	G4RunManager runManager;
	init::InitMessengers initMessengers(runManager);

	auto uiManager = G4UImanager::GetUIpointer();

	if (parser->GetArgc() > 1) {
		closure(runManager);

		// first argument is a script file name
		const G4String command = "/control/execute ";
		const G4String fileName = parser->GetArgv()[1];
		uiManager->ApplyCommand(command + fileName);
	} else {
#ifdef	G4VIS_USE
#ifndef	ISNPEMULIB_NO_VIS
		auto const visManager = new G4VisExecutive("Quiet");
		visManager->Initialize();

		// no arguments passed to executable - run in visual mode
		auto ui = new G4UIExecutive(parser->GetArgc(), parser->GetArgv());

		closure(runManager);

		uiManager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
#endif
#endif	//	G4VIS_USE
	}

	return 0;
}

}

}
