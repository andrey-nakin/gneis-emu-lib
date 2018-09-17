#include "isnp/util/FileNameBuilder.hh"
#include "isnp/init/FileNameBuilderMessenger.hh"

namespace isnp {

namespace init {

#define DIR "/isnp/fileName/"

static std::unique_ptr<G4UIcmdWithAString> MakeCommonSuffix(
		FileNameBuilderMessenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithAString > (DIR "suffix", inst);
	result->SetGuidance("Set a common name suffix for all files produced");
	result->SetParameterName("suffix", false);

	return result;

}

FileNameBuilderMessenger::FileNameBuilderMessenger() :
		commonSuffixCmd(MakeCommonSuffix(this)) {

}

FileNameBuilderMessenger::~FileNameBuilderMessenger() {

}

G4String FileNameBuilderMessenger::GetCurrentValue(G4UIcommand* const command) {

	G4String ans;

	if (command == commonSuffixCmd.get()) {
		ans = util::FileNameBuilder::GetCommonSuffix();
	}

	return ans;

}

void FileNameBuilderMessenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == commonSuffixCmd.get()) {
		util::FileNameBuilder::SetCommonSuffix(newValue);
	}

}

}

}
