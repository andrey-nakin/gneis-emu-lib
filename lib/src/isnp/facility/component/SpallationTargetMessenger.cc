#include "isnp/facility/component/SpallationTargetMessenger.hh"

namespace isnp {

namespace facility {

namespace component {

#define DIR "/isnp/facility/component/spTarget/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("Spallation Target Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWithABool> MakeHasCooler(
		SpallationTargetMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithABool > (DIR "hasCooler", inst);
	result->SetGuidance("Add a cooling contour to the spallation target.");
	result->SetGuidance("Choice : true, 1, false, 0");
	result->SetParameterName("value", true);
	result->SetDefaultValue("true");
	result->AvailableForStates(G4State_PreInit);

	return result;

}

SpallationTargetMessenger::SpallationTargetMessenger(
		SpallationTarget& aComponent) :
		component(aComponent), directory(MakeDirectory()), hasCoolerCmd(
				MakeHasCooler(this)) {
}

SpallationTargetMessenger::~SpallationTargetMessenger() {
}

G4String SpallationTargetMessenger::GetCurrentValue(
		G4UIcommand* const command) {

	G4String ans;

	if (command == hasCoolerCmd.get()) {
		ans = component.GetHasCooler() ? "1" : "0";
	}

	return ans;

}

void SpallationTargetMessenger::SetNewValue(G4UIcommand* const command,
		G4String newValue) {

	if (command == hasCoolerCmd.get()) {
		component.SetHasCooler(hasCoolerCmd->GetNewBoolValue(newValue));
	}

}

}

}

}
