#ifndef isnp_util_FileNameBuilderMessenger_hh
#define isnp_util_FileNameBuilderMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

namespace isnp {

namespace util {

/**
 * Helper class for random number generation.
 */
class FileNameBuilderMessenger: public G4UImessenger {
public:

	FileNameBuilderMessenger();
	~FileNameBuilderMessenger();

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	std::unique_ptr<G4UIcmdWithAString> const commonSuffixCmd;

};

}

}

#endif	//	isnp_util_FileNameBuilderMessenger_hh
