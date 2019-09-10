#ifndef isnp_init_PhysListMessenger_hh
#define isnp_init_PhysListMessenger_hh

#include <memory>

#include <G4RunManager.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

namespace isnp {

namespace init {

class PhysListMessenger: public G4UImessenger {
public:

	PhysListMessenger(G4RunManager& aRunManager);
	~PhysListMessenger();

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	G4RunManager& runManager;
	std::unique_ptr<G4UIcmdWithAString> const physListCmd;
	G4String physList;

	void SetPhysList(G4String const& name);

};

}

}

#endif	//	isnp_init_PhysListMessenger_hh
