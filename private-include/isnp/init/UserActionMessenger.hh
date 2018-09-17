#ifndef isnp_init_UserActionMessenger_hh
#define isnp_init_UserActionMessenger_hh

#include <memory>

#include <G4RunManager.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

namespace isnp {

namespace init {

class UserActionMessenger: public G4UImessenger {
public:

	UserActionMessenger(G4RunManager& aRunManager);
	~UserActionMessenger();

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	G4RunManager& runManager;
	std::unique_ptr<G4UIcmdWithAString> const userActionCmd;
	G4String userAction;

	void SetUserAction(G4String const& name);

};

}

}

#endif	//	isnp_init_UserActionMessenger_hh
