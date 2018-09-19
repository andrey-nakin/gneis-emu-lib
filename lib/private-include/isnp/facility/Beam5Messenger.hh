#ifndef isnp_facility_Beam5Messenger_hh
#define isnp_facility_Beam5Messenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcommand.hh>
#include <G4UIcmdWithAString.hh>

#include "isnp/facility/Beam5.hh"

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;

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
	std::unique_ptr<G4UIcmdWithADoubleAndUnit> const diameterCmd, angleCmd;
	std::unique_ptr<G4UIcmdWithAnInteger> const verboseCmd;
	std::unique_ptr<G4UIcmdWithAString> const c5MaterialCmd;

};

}

}

#endif	//	isnp_facility_Beam5Messenger_hh
