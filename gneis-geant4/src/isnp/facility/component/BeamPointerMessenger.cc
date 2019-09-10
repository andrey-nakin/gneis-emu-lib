#include <G4UnitsTable.hh>
#include "isnp/facility/component/BeamPointerMessenger.hh"

namespace isnp {

namespace facility {

namespace component {

#define DIR "/isnp/facility/component/beamPointer/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("Beam Pointer Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWith3VectorAndUnit> MakePosition(
		BeamPointerMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWith3VectorAndUnit
			> (DIR "position", inst);
	result->SetGuidance("Beam starting position");
	result->SetParameterName("PositionX", "PositionY", "PositionZ", false);
	result->SetDefaultUnit("mm");
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

static std::unique_ptr<G4UIcmdWith3VectorAndUnit> MakeRotation(
		BeamPointerMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWith3VectorAndUnit
			> (DIR "rotation", inst);
	result->SetGuidance("Beam direction");
	result->SetParameterName("RotationX", "RotationY", "RotationZ", false);
	result->SetDefaultUnit("deg");
	result->SetUnitCategory(G4UnitDefinition::GetCategory("deg"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

BeamPointerMessenger::BeamPointerMessenger(BeamPointer& aComponent) :
		component(aComponent), directory(MakeDirectory()), rotationCmd(
				MakeRotation(this)), positionCmd(MakePosition(this)) {
}

BeamPointerMessenger::~BeamPointerMessenger() {
}

G4String BeamPointerMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == rotationCmd.get()) {
		ans = rotationCmd->ConvertToStringWithBestUnit(component.GetRotation());
	} else if (command == positionCmd.get()) {
		ans = positionCmd->ConvertToStringWithBestUnit(component.GetPosition());
	}

	return ans;

}

void BeamPointerMessenger::SetNewValue(G4UIcommand* const command,
		G4String newValue) {

	if (command == rotationCmd.get()) {
		component.SetRotation(rotationCmd->GetNew3VectorValue(newValue));
	} else if (command == positionCmd.get()) {
		component.SetPosition(positionCmd->GetNew3VectorValue(newValue));
	}

}

}

}

}
