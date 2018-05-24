#include <G4UnitsTable.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include "G4UIcmdWithAnInteger.hh"

#include "isnp/facility/BasicSpallationMessenger.hh"

namespace isnp {

namespace facility {

#define DIR "/isnp/basicSpallation/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("ISNP Basic Spallation Facility Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeHorizontalAngle(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "horizontalAngle", inst);
	result->SetGuidance("Set horizontal rotation");
	result->SetParameterName("angle", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("deg"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeVerticalAngle(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "verticalAngle", inst);
	result->SetGuidance("Set vertical rotation");
	result->SetParameterName("angle", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("deg"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDistance(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "distance", inst);
	result->SetGuidance("Set range from the center of the spallation target");
	result->SetParameterName("distance", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("m"));
	result->AvailableForStates(G4State_PreInit);
	result->SetRange("distance >0");

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDetectorWidth(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "detectorWidth", inst);
	result->SetGuidance("Set width of the detector");
	result->SetParameterName("width", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("m"));
	result->AvailableForStates(G4State_PreInit);
	result->SetRange("width >0");

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDetectorHeight(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "detectorHeight", inst);
	result->SetGuidance("Set height of the detector");
	result->SetParameterName("height", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("m"));
	result->AvailableForStates(G4State_PreInit);
	result->SetRange("height >0");

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDetectorLength(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "detectorLength", inst);
	result->SetGuidance("Set length of the detector");
	result->SetParameterName("length", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("m"));
	result->AvailableForStates(G4State_PreInit);
	result->SetRange("length >0");

	return result;

}

static std::unique_ptr<G4UIcmdWithAnInteger> MakeVerbose(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAnInteger
			> (DIR "verbose", inst);
	result->SetGuidance(
			"Set the Verbose level of ISNP basic spallation facility.");
	result->SetGuidance(" 0 : Silent (default)");
	result->SetGuidance(" 1 : Display warning messages");
	result->SetGuidance(" 2 : Display more");
	result->SetParameterName("level", true);
	result->SetDefaultValue(0);
	result->SetRange("level >=0 && level <=3");

	return result;

}

static std::unique_ptr<G4UIcmdWithAString> MakeWorldMaterial(
		BasicSpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAString
			> (DIR "worldMaterial", inst);
	result->SetGuidance("Set a material of world");
	result->SetParameterName("material", false);
	result->AvailableForStates(G4State_PreInit, G4State_Idle);

	return result;

}

BasicSpallationMessenger::BasicSpallationMessenger(BasicSpallation& aFacility) :
		facility(aFacility), directory(MakeDirectory()), horizontalAngleCmd(
				MakeHorizontalAngle(this)), verticalAngleCmd(
				MakeVerticalAngle(this)), distanceCmd(MakeDistance(this)), detectorWidthCmd(
				MakeDetectorWidth(this)), detectorHeightCmd(
				MakeDetectorHeight(this)), detectorLengthCmd(
				MakeDetectorLength(this)), verboseCmd(MakeVerbose(this)), worldMaterialCmd(
				MakeWorldMaterial(this)) {

}

BasicSpallationMessenger::~BasicSpallationMessenger() {

}

G4String BasicSpallationMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == horizontalAngleCmd.get()) {
		ans = horizontalAngleCmd->ConvertToString(
				facility.GetHorizontalAngle());
	} else if (command == verticalAngleCmd.get()) {
		ans = verticalAngleCmd->ConvertToString(facility.GetVerticalAngle());
	} else if (command == distanceCmd.get()) {
		ans = distanceCmd->ConvertToString(facility.GetDistance());
	} else if (command == detectorWidthCmd.get()) {
		ans = detectorWidthCmd->ConvertToString(facility.GetDetectorWidth());
	} else if (command == detectorHeightCmd.get()) {
		ans = detectorHeightCmd->ConvertToString(facility.GetDetectorHeight());
	} else if (command == detectorLengthCmd.get()) {
		ans = detectorLengthCmd->ConvertToString(facility.GetDetectorLength());
	} else if (command == verboseCmd.get()) {
		ans = verboseCmd->ConvertToString(facility.GetVerboseLevel());
	} else if (command == worldMaterialCmd.get()) {
		ans = facility.GetWorldMaterial();
	}

	return ans;

}

void BasicSpallationMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == horizontalAngleCmd.get()) {
		facility.SetHorizontalAngle(
				horizontalAngleCmd->GetNewDoubleValue(newValue));
	} else if (command == verticalAngleCmd.get()) {
		facility.SetVerticalAngle(
				verticalAngleCmd->GetNewDoubleValue(newValue));
	} else if (command == distanceCmd.get()) {
		facility.SetDistance(distanceCmd->GetNewDoubleValue(newValue));
	} else if (command == detectorWidthCmd.get()) {
		facility.SetDetectorWidth(
				detectorWidthCmd->GetNewDoubleValue(newValue));
	} else if (command == detectorHeightCmd.get()) {
		facility.SetDetectorHeight(
				detectorHeightCmd->GetNewDoubleValue(newValue));
	} else if (command == detectorLengthCmd.get()) {
		facility.SetDetectorLength(
				detectorLengthCmd->GetNewDoubleValue(newValue));
	} else if (command == verboseCmd.get()) {
		facility.SetVerboseLevel(verboseCmd->GetNewIntValue(newValue));
	} else if (command == worldMaterialCmd.get()) {
		facility.SetWorldMaterial(newValue);
	}

}

}

}
