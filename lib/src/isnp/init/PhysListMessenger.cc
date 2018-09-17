#include <algorithm>
#include <G4PhysListFactory.hh>
#include "isnp/init/PhysListMessenger.hh"

namespace isnp {

namespace init {

#define DIR "/isnp/"

static std::unique_ptr<G4UIcmdWithAString> MakePhysList(
		PhysListMessenger* const inst) {

	G4PhysListFactory factory;
	auto physLists = factory.AvailablePhysLists();

	std::string candidates;
	std::for_each(std::begin(physLists), std::end(physLists),
			[&candidates](G4String& pl) {
				candidates += pl;
				candidates += ' ';
			});

	auto result = std::make_unique < G4UIcmdWithAString
			> (DIR "physList", inst);
	result->SetGuidance("Set physics list");
	result->SetParameterName("physList", false);
	result->AvailableForStates(G4State_PreInit);
	result->SetCandidates(candidates.c_str());

	return result;

}

PhysListMessenger::PhysListMessenger(G4RunManager& aRunManager) :
		runManager(aRunManager), physListCmd(MakePhysList(this)), physList("") {

}

PhysListMessenger::~PhysListMessenger() {

}

G4String PhysListMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == physListCmd.get()) {
		ans = physList;
	}

	return ans;

}

void PhysListMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == physListCmd.get()) {
		SetPhysList(newValue);
	}

}

void PhysListMessenger::SetPhysList(G4String const& name) {

	G4PhysListFactory factory;

	if (!name.isNull() && factory.IsReferencePhysList(name)) {
		auto const pl = factory.GetReferencePhysList(name);
		if (pl) {
			runManager.SetUserInitialization(pl);
		} else {
			G4cerr << "Unknown physics list: " << name << G4endl;
			return;
		}
	}

	physList = name;

}

}

}
