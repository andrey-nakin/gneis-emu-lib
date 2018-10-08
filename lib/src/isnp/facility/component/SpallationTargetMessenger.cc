#include <G4UnitsTable.hh>
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

static std::unique_ptr<G4UIcmdWith3VectorAndUnit> MakePosition(
		SpallationTargetMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWith3VectorAndUnit
			> (DIR "position", inst);
	result->SetGuidance("Spallation target position");
	result->SetParameterName("PositionX", "PositionY", "PositionZ", false);
	result->SetDefaultUnit("mm");
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

static std::unique_ptr<G4UIcmdWith3VectorAndUnit> MakeRotation(
		SpallationTargetMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWith3VectorAndUnit
			> (DIR "rotation", inst);
	result->SetGuidance("Spallation target rotation");
	result->SetParameterName("RotationX", "RotationY", "RotationZ", false);
	result->SetDefaultUnit("deg");
	result->SetUnitCategory(G4UnitDefinition::GetCategory("deg"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

SpallationTargetMessenger::SpallationTargetMessenger(
		SpallationTarget& aComponent) :
		component(aComponent), directory(MakeDirectory()), hasCoolerCmd(
				MakeHasCooler(this)), rotationCmd(MakeRotation(this)), positionCmd(
				MakePosition(this)) {
}

SpallationTargetMessenger::~SpallationTargetMessenger() {
}

G4String SpallationTargetMessenger::GetCurrentValue(
		G4UIcommand* const command) {

	G4String ans;

	if (command == hasCoolerCmd.get()) {
		ans = component.GetHasCooler() ? "1" : "0";
	} else if (command == rotationCmd.get()) {
		ans = rotationCmd->ConvertToStringWithBestUnit(component.GetRotation());
	} else if (command == positionCmd.get()) {
		ans = positionCmd->ConvertToStringWithBestUnit(component.GetPosition());
	}

	return ans;

}

void SpallationTargetMessenger::SetNewValue(G4UIcommand* const command,
		G4String newValue) {

	if (command == hasCoolerCmd.get()) {
		component.SetHasCooler(hasCoolerCmd->GetNewBoolValue(newValue));
	} else if (command == rotationCmd.get()) {
		component.SetRotation(rotationCmd->GetNew3VectorValue(newValue));
	} else if (command == positionCmd.get()) {
		component.SetPosition(positionCmd->GetNew3VectorValue(newValue));
	}

}

}

}

}
