#include <G4UnitsTable.hh>

#include "isnp/generator/ResamplingMessenger.hh"

namespace isnp {

namespace generator {

#define DIR "/isnp/gun/resampling/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("ISNP Resampling Gun Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWithAnInteger> MakeVerbose(
		ResamplingMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAnInteger
			> (DIR "verbose", inst);
	result->SetGuidance("Set the Verbose level of ISNP Resampling gun.");
	result->SetGuidance(" 0 : Silent (default)");
	result->SetGuidance(" 1 : Display warning messages");
	result->SetGuidance(" 2 : Display more");
	result->SetParameterName("level", true);
	result->SetDefaultValue(0);
	result->SetRange("level >=0 && level <=3");

	return result;

}

static std::unique_ptr<G4UIcmdWithAString> MakeFile(
		ResamplingMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAString > (DIR "file", inst);
	result->SetGuidance("Set a data file name");
	result->SetParameterName("file", true);

	return result;

}

ResamplingMessenger::ResamplingMessenger(Resampling& aGenerator) :
		generator(aGenerator), directory(MakeDirectory()), verboseCmd(
				MakeVerbose(this)), fileCmd(MakeFile(this)) {

}

ResamplingMessenger::~ResamplingMessenger() {

}

G4String ResamplingMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == verboseCmd.get()) {
		ans = verboseCmd->ConvertToString(generator.GetVerboseLevel());
	} else if (command == fileCmd.get()) {
		ans = generator.GetSampleFileName();
	}

	return ans;

}

void ResamplingMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == verboseCmd.get()) {
		generator.SetVerboseLevel(verboseCmd->GetNewIntValue(newValue));
	} else if (command == fileCmd.get()) {
		generator.SetSampleFileName(newValue);
	}

}

}

}
