#include <G4UnitsTable.hh>
#include "G4UIcmdWithAnInteger.hh"
#include <G4UIcmdWithADoubleAndUnit.hh>

#include "isnp/generator/SpallationMessenger.hh"

namespace isnp {

namespace generator {

#define DIR "/isnp/spallation/gun/"

namespace mode {

static G4String const GaussianEllipse = "GaussianEllipse";
static G4String const UniformCircle = "UniformCircle";
static G4String const UniformRectangle = "UniformRectangle";

}

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

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeXWidth(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "xWidth", inst);
	result->SetGuidance("Set the FWHM of the beam along X axis");
	result->SetParameterName("width", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeYWidth(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "yWidth", inst);
	result->SetGuidance("Set the FWHM of the beam along Y axis");
	result->SetParameterName("width", false);
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

static std::unique_ptr<G4UIcmdWithAString> MakeMode(
		SpallationMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAString > (DIR "mode", inst);
	result->SetGuidance("Set a beam distribution mode");

	G4String const g = G4String("  mode: ") + mode::GaussianEllipse + ", "
			+ mode::UniformCircle + ", " + mode::UniformRectangle;
	result->SetGuidance(g);
	result->SetParameterName("mode", false);
	G4String const c = mode::GaussianEllipse + " " + mode::UniformCircle + " "
			+ mode::UniformRectangle;
	result->SetCandidates(c);

	return result;

}

SpallationMessenger::SpallationMessenger(Spallation& spallation_) :
		spallation(spallation_), directory(MakeDirectory()), diameterCmd(
				MakeDiameter(this)), xWidthCmd(MakeXWidth(this)), yWidthCmd(
				MakeYWidth(this)), positionXCmd(MakePositionX(this)), positionYCmd(
				MakePositionY(this)), verboseCmd(MakeVerbose(this)), modeCmd(
				MakeMode(this)) {

}

SpallationMessenger::~SpallationMessenger() {

}

G4String SpallationMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == diameterCmd.get()) {
		ans = diameterCmd->ConvertToString(
				spallation.GetUniformCircle().GetProps().GetDiameter());
	} else if (command == xWidthCmd.get()) {
		ans = xWidthCmd->ConvertToString(spallation.GetGaussEllipse().GetProps().GetXWidth());
	} else if (command == yWidthCmd.get()) {
		ans = yWidthCmd->ConvertToString(spallation.GetGaussEllipse().GetProps().GetYWidth());
	} else if (command == positionXCmd.get()) {
		ans = positionXCmd->ConvertToString(spallation.GetPositionX());
	} else if (command == positionYCmd.get()) {
		ans = positionYCmd->ConvertToString(spallation.GetPositionY());
	} else if (command == verboseCmd.get()) {
		ans = verboseCmd->ConvertToString(spallation.GetVerboseLevel());
	} else if (command == modeCmd.get()) {
		ans = ModeToString(spallation.GetMode());
	}

	return ans;

}

void SpallationMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == diameterCmd.get()) {
		spallation.GetUniformCircle().GetProps().SetDiameter(
				diameterCmd->GetNewDoubleValue(newValue));
	} else if (command == xWidthCmd.get()) {
		spallation.GetGaussEllipse().GetProps().SetXWidth(
				xWidthCmd->GetNewDoubleValue(newValue));
		spallation.GetUniformRectangle().GetProps().SetXWidth(
				xWidthCmd->GetNewDoubleValue(newValue));
	} else if (command == yWidthCmd.get()) {
		spallation.GetGaussEllipse().GetProps().SetYWidth(
				yWidthCmd->GetNewDoubleValue(newValue));
		spallation.GetUniformRectangle().GetProps().SetYWidth(
				yWidthCmd->GetNewDoubleValue(newValue));
	} else if (command == positionXCmd.get()) {
		spallation.SetPositionX(positionXCmd->GetNewDoubleValue(newValue));
	} else if (command == positionYCmd.get()) {
		spallation.SetPositionY(positionYCmd->GetNewDoubleValue(newValue));
	} else if (command == verboseCmd.get()) {
		spallation.SetVerboseLevel(verboseCmd->GetNewIntValue(newValue));
	} else if (command == modeCmd.get()) {
		spallation.SetMode(StringToMode(newValue));
	}

}

G4String SpallationMessenger::ModeToString(Spallation::Mode mode) {

	switch (mode) {
	case Spallation::Mode::GaussianEllipse:
		return mode::GaussianEllipse;

	case Spallation::Mode::UniformCircle:
		return mode::UniformCircle;

	case Spallation::Mode::UniformRectangle:
		return mode::UniformRectangle;
	}

	return "";

}

Spallation::Mode SpallationMessenger::StringToMode(G4String const& mode) {

	if (mode == mode::GaussianEllipse) {
		return Spallation::Mode::GaussianEllipse;
	}

	if (mode == mode::UniformCircle) {
		return Spallation::Mode::UniformCircle;
	}

	if (mode == mode::UniformRectangle) {
		return Spallation::Mode::UniformRectangle;
	}

	return Spallation::Mode::GaussianEllipse;

}

}

}
