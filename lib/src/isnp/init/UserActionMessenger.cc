#include <string>
#include "isnp/init/UserActionMessenger.hh"
#include "isnp/generator/Spallation.hh"
#include "isnp/generator/Resampling.hh"

namespace isnp {

namespace init {

#define DIR "/isnp/"

namespace userAction {

static const G4String Spallation = "spallation";
static const G4String Resampling = "resampling";

}

static std::unique_ptr<G4UIcmdWithAString> MakeUserAction(
		UserActionMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAString > (DIR "gun", inst);
	result->SetGuidance("Use given ISNP gun: ");
	std::string const guidance = userAction::Spallation + ", "
			+ userAction::Resampling;
	result->SetGuidance(guidance.c_str());
	result->SetParameterName("name", false);
	result->AvailableForStates(G4State_PreInit);
	std::string const candidates = userAction::Spallation + " "
			+ userAction::Resampling;
	result->SetCandidates(candidates.c_str());

	return result;

}

UserActionMessenger::UserActionMessenger(G4RunManager& aRunManager) :
		runManager(aRunManager), userActionCmd(MakeUserAction(this)), userAction(
				"") {

}

UserActionMessenger::~UserActionMessenger() {

}

G4String UserActionMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == userActionCmd.get()) {
		ans = userAction;
	}

	return ans;

}

void UserActionMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == userActionCmd.get()) {
		SetUserAction(newValue);
	}

}

void UserActionMessenger::SetUserAction(G4String const& name) {

	if (name == userAction::Spallation) {

		runManager.SetUserAction(new isnp::generator::Spallation);

	} else if (name == userAction::Resampling) {

		runManager.SetUserAction(new isnp::generator::Resampling);

	} else {

		G4cerr << "Unknown ISNP user action name: " << name << G4endl;
		return;

	}

	userAction = name;

}

}

}
