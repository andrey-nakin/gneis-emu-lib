#ifndef isnp_facility_Beam5Messenger_hh
#define isnp_facility_Beam5Messenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcommand.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

#include "isnp/facility/Beam5.hh"

namespace isnp {

namespace facility {

class Beam5Messenger: public G4UImessenger {
public:

	Beam5Messenger(Beam5& facility);
	~Beam5Messenger();

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	Beam5& facility;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithADoubleAndUnit> const c5DiameterCmd, xAngleCmd,
			yAngleCmd;
	std::unique_ptr<G4UIcmdWithAnInteger> const verboseCmd;
	std::unique_ptr<G4UIcmdWithAString> const c5MaterialCmd;
	std::unique_ptr<G4UIcmdWithABool> const hasTargetCmd;

};

}

}

#endif	//	isnp_facility_Beam5Messenger_hh
