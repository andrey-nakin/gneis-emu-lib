#include <G4UnitsTable.hh>
#include "G4UIcmdWithAnInteger.hh"
#include <G4UIcmdWithADoubleAndUnit.hh>

#include "isnp/generator/SpallationMessenger.hh"

namespace isnp {

namespace generator {

#define DIR "/isnp/spallation/gun/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("ISNP Spallation Gun Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDiameter(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "diameter", inst);
	result->SetGuidance("Set the diameter of the beam");
	result->SetParameterName("diameter", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakePositionX(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "positionX", inst);
	result->SetGuidance("Set the X position of the beam's center");
	result->SetParameterName("position", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakePositionY(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "positionY", inst);
	result->SetGuidance("Set the Y position of the beam's center");
	result->SetParameterName("position", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));

	return result;

}

static std::unique_ptr<G4UIcmdWithAnInteger> MakeVerbose(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAnInteger
			> (DIR "verbose", inst);
	result->SetGuidance("Set the Verbose level of ISNP spallation gun.");
	result->SetGuidance(" 0 : Silent (default)");
	result->SetGuidance(" 1 : Display warning messages");
	result->SetGuidance(" 2 : Display more");
	result->SetParameterName("level", true);
	result->SetDefaultValue(0);
	result->SetRange("level >=0 && level <=3");

	return result;

}

SpallationMessenger::SpallationMessenger(Spallation& spallation_) :
		spallation(spallation_), directory(MakeDirectory()), diameterCmd(
				MakeDiameter(this)), positionXCmd(MakePositionX(this)), positionYCmd(
				MakePositionY(this)), verboseCmd(MakeVerbose(this)) {

}

SpallationMessenger::~SpallationMessenger() {

}

G4String SpallationMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == diameterCmd.get()) {
		ans = diameterCmd->ConvertToString(spallation.GetUcProps().GetDiameter());
	} else if (command == positionXCmd.get()) {
		ans = positionXCmd->ConvertToString(spallation.GetPositionX());
	} else if (command == positionYCmd.get()) {
		ans = positionYCmd->ConvertToString(spallation.GetPositionY());
	} else if (command == verboseCmd.get()) {
		ans = verboseCmd->ConvertToString(spallation.GetVerboseLevel());
	}

	return ans;

}

void SpallationMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == diameterCmd.get()) {
		spallation.GetUcProps().SetDiameter(diameterCmd->GetNewDoubleValue(newValue));
	} else if (command == positionXCmd.get()) {
		spallation.SetPositionX(positionXCmd->GetNewDoubleValue(newValue));
	} else if (command == positionYCmd.get()) {
		spallation.SetPositionY(positionYCmd->GetNewDoubleValue(newValue));
	} else if (command == verboseCmd.get()) {
		spallation.SetVerboseLevel(verboseCmd->GetNewIntValue(newValue));
	}

}

}

}
