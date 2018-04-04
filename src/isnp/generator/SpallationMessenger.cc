#include <G4UnitsTable.hh>

#include "isnp/generator/SpallationMessenger.hh"

namespace isnp {

namespace generator {

#define DIR "/isnp/gun/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("ISNP Spallation Gun Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDiameter(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "diameter", inst);
	result->SetGuidance("Set a diameter of the beam");
	result->SetParameterName("diameter", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));
	result->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle,
			G4State_GeomClosed, G4State_EventProc);

	return result;

}

SpallationMessenger::SpallationMessenger(Spallation& spallation_) :
		spallation(spallation_), directory(MakeDirectory()), cmdDiameter(
				MakeDiameter(this)) {

}

void SpallationMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == cmdDiameter.get()) {
		spallation.SetDiameter(cmdDiameter->GetNewDoubleValue(newValue));
	}

}

}

}
