#include <chrono>

#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <Randomize.hh>
#ifdef G4VIS_USE
#ifndef	ISNPEMULIB_NO_VIS
#include <G4VisExecutive.hh>
#endif
#endif	//	G4VIS_USE
#include <QGSP_INCLXX_HP.hh>
#include <QGSP_BERT_HP.hh>
#include <QGSP_BIC_HP.hh>
#include <FTFP_INCLXX_HP.hh>
#include <FTFP_BERT_HP.hh>

#include "isnp/runner/BasicRunner.hh"
#include "isnp/runner/CommandLineParser.hh"
#include "isnp/util/FileNameBuilder.hh"

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

	isnp::util::FileNameBuilder::SetCommonSuffix(parser->GetFileSuffix());

	G4RunManager runManager;

	G4Random::setTheSeed(
			parser->IsRandomSeedSet() ? parser->GetRandomSeed() : SystemTime());

	if (!parser->GetPlName().isNull()) {
		auto const pl = DetectPhysicsList(parser->GetPlName());
		if (pl) {
			runManager.SetUserInitialization(pl);
		}
	}
	ValidateSettings(runManager);

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

		uiManager->ApplyCommand("/run/initialize");
		uiManager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
#endif
#endif	//	G4VIS_USE
	}

	return 0;
}

long BasicRunner::SystemTime() {
	using namespace std::chrono;
	auto const now = time_point_cast < milliseconds > (system_clock::now());
	auto const value = now.time_since_epoch();
	return value.count();
}

G4VUserPhysicsList* BasicRunner::DetectPhysicsList(G4String const& name) const {

	if (name == "-") {
		return nullptr;
	}

#define	PL(n) if (name == #n) { return new n; }

	PL(QGSP_BERT_HP)
	PL(QGSP_BIC_HP)
	PL(QGSP_INCLXX_HP)
	PL(FTFP_BERT_HP)
	PL(FTFP_INCLXX_HP)

#undef PL

	return nullptr;

}

void BasicRunner::ValidateSettings(G4RunManager& runManager) const {

	if (!runManager.GetUserPhysicsList()) {
		runManager.SetUserInitialization(new QGSP_BERT_HP);
	}

}

}

}
