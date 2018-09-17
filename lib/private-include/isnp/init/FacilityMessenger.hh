#ifndef isnp_init_FacilityMessenger_hh
#define isnp_init_FacilityMessenger_hh

#include <memory>

#include <G4RunManager.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

namespace isnp {

namespace init {

class FacilityMessenger: public G4UImessenger {
public:

	FacilityMessenger(G4RunManager& aRunManager);
	~FacilityMessenger();

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	G4RunManager& runManager;
	std::unique_ptr<G4UIcmdWithAString> const facilityCmd;
	G4String facility;

	void SetFacility(G4String const& name);

};

}

}

#endif	//	isnp_init_FacilityMessenger_hh
