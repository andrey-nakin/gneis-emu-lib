#ifndef isnp_generator_SpallationMessenger_hh
#define isnp_generator_SpallationMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

#include "isnp/generator/Spallation.hh"

namespace isnp {

namespace generator {

class SpallationMessenger: public G4UImessenger {
public:

	SpallationMessenger(Spallation& spallation);

    void SetNewValue(G4UIcommand*, G4String) override;

private:

	Spallation& spallation;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithADoubleAndUnit> const cmdDiameter;

};

}

}

#endif	//	isnp_generator_SpallationMessenger_hh
