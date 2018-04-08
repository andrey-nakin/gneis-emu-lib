#ifndef isnp_facility_Beam5Messenger_hh
#define isnp_facility_Beam5Messenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcommand.hh>

#include "isnp/facility/Beam5.hh"

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;

namespace isnp {

namespace facility {

class Beam5Messenger: public G4UImessenger {
public:

	Beam5Messenger(Beam5& facility);
	~Beam5Messenger();

	void SetNewValue(G4UIcommand*, G4String) override;

private:

	Beam5& facility;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithADoubleAndUnit> const diameterCmd, angleCmd;
	std::unique_ptr<G4UIcmdWithABool> const haveCollimator1Cmd,
			haveCollimator2Cmd, haveCollimator3Cmd, haveCollimator4Cmd,
			haveCollimator5Cmd;
	std::unique_ptr<G4UIcmdWithAnInteger> const verboseCmd;

};

}

}

#endif	//	isnp_facility_Beam5Messenger_hh
