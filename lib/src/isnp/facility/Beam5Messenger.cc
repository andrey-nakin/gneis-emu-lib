#include <sstream>
#include <string>

#include <G4UnitsTable.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"

#include "isnp/facility/Beam5Messenger.hh"

namespace isnp {

namespace facility {

#define DIR "/isnp/facility/beam5/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("ISNP Beam #5 Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDiameter(
		Beam5Messenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "diameter", inst);
	result->SetGuidance("Set the final collimator's diameter");
	result->SetParameterName("diameter", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));
	result->AvailableForStates(G4State_PreInit);
	result->SetRange("diameter >0");

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeAngle(
		Beam5Messenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "angle", inst);
	result->SetGuidance("Set the final collimator's diameter");
	result->SetParameterName("angle", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("deg"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

static std::unique_ptr<G4UIcmdWithAnInteger> MakeVerboseLevel(
		Beam5Messenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAnInteger
			> (DIR "verbose", inst);
	result->SetGuidance("Set the Verbose level of ISNP beam #5.");
	result->SetGuidance(" 0 : Silent (default)");
	result->SetGuidance(" 1 : Display warning messages");
	result->SetGuidance(" 2 : Display more");
	result->SetParameterName("level", true);
	result->SetDefaultValue(0);
	result->SetRange("level >=0 && level <=3");

	return result;

}

static std::unique_ptr<G4UIcmdWithAString> MakeC5Material(
		Beam5Messenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAString
			> (DIR "c5/material", inst);
	result->SetGuidance("Set a material of collimator #5");
	result->SetParameterName("material", false);
	result->AvailableForStates(G4State_PreInit);

	return result;

}

Beam5Messenger::Beam5Messenger(Beam5& facility_) :
		facility(facility_), directory(MakeDirectory()), diameterCmd(
				MakeDiameter(this)), angleCmd(MakeAngle(this)), verboseCmd(
				MakeVerboseLevel(this)), c5MaterialCmd(MakeC5Material(this)) {

}

Beam5Messenger::~Beam5Messenger() {

}

G4String Beam5Messenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == diameterCmd.get()) {
		ans = diameterCmd->ConvertToString(facility.GetDiameter());
	} else if (command == angleCmd.get()) {
		ans = angleCmd->ConvertToString(facility.GetAngle());
	} else if (command == verboseCmd.get()) {
		ans = verboseCmd->ConvertToString(facility.GetVerboseLevel());
	} else if (command == c5MaterialCmd.get()) {
		ans = facility.GetC5Material();
	}

	return ans;

}

void Beam5Messenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == diameterCmd.get()) {
		facility.SetDiameter(diameterCmd->GetNewDoubleValue(newValue));
	} else if (command == angleCmd.get()) {
		facility.SetAngle(angleCmd->GetNewDoubleValue(newValue));
	} else if (command == verboseCmd.get()) {
		facility.SetVerboseLevel(verboseCmd->GetNewIntValue(newValue));
	} else if (command == c5MaterialCmd.get()) {
		facility.SetC5Material(newValue);
	}

}

}

}
