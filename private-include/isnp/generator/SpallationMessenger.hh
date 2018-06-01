#ifndef isnp_generator_SpallationMessenger_hh
#define isnp_generator_SpallationMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcommand.hh>

#include "isnp/generator/Spallation.hh"

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

namespace isnp {

namespace generator {

class SpallationMessenger: public G4UImessenger {
public:

	SpallationMessenger(Spallation& spallation);
	~SpallationMessenger();

	void SetNewValue(G4UIcommand*, G4String) override;

private:

	Spallation& spallation;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithADoubleAndUnit> const diameterCmd, positionXCmd, positionYCmd;
	std::unique_ptr<G4UIcmdWithAnInteger> const verboseCmd;

};

}

}

#endif	//	isnp_generator_SpallationMessenger_hh
