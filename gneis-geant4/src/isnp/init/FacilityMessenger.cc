#include <string>
#include "isnp/init/FacilityMessenger.hh"
#include "isnp/facility/Beam5.hh"
#include "isnp/facility/BasicSpallation.hh"

namespace isnp {

namespace init {

#define DIR "/isnp/"

namespace facility {

static const G4String Beam5 = "beam5";
static const G4String BasicSpallation = "basicSpallation";

}

static std::unique_ptr<G4UIcmdWithAString> MakeFacility(
		FacilityMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAString
			> (DIR "facility", inst);
	result->SetGuidance("Use given ISNP facility: ");
	std::string const guidance = facility::Beam5 + ", "
			+ facility::BasicSpallation;
	result->SetGuidance(guidance.c_str());
	result->SetParameterName("name", false);
	result->AvailableForStates(G4State_PreInit);
	std::string const candidates = facility::Beam5 + " "
			+ facility::BasicSpallation;
	result->SetCandidates(candidates.c_str());

	return result;

}

FacilityMessenger::FacilityMessenger(G4RunManager& aRunManager) :
		runManager(aRunManager), facilityCmd(MakeFacility(this)), facility(
				nullptr), facilityName("") {

}

FacilityMessenger::~FacilityMessenger() {

}

G4String FacilityMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == facilityCmd.get()) {
		ans = facilityName;
	}

	return ans;

}

void FacilityMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == facilityCmd.get()) {
		SetFacility(newValue);
	}

}

void FacilityMessenger::SetFacility(G4String const& name) {

	if (facilityName != name) {

		if (name == facility::Beam5) {

			if (facility) {
				delete facility;
			}

			runManager.SetUserInitialization(
					isnp::facility::Beam5::GetInstance());

		} else if (name == facility::BasicSpallation) {

			if (facility) {
				delete facility;
			}

			runManager.SetUserInitialization(
					isnp::facility::BasicSpallation::GetInstance());

		} else {

			G4cerr << "Unknown ISNP facility name: " << name << G4endl;
			return;

		}

		facilityName = name;
	}

}

}

}
