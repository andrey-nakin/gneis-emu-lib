#ifndef	isnp_facility_component_SpallationTargetMessenger_hh
#define	isnp_facility_component_SpallationTargetMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include "isnp/facility/component/SpallationTarget.hh"

namespace isnp {

namespace facility {

namespace component {

class SpallationTargetMessenger: public G4UImessenger {
public:

	SpallationTargetMessenger(SpallationTarget& component);
	~SpallationTargetMessenger() override;

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	SpallationTarget& component;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithABool> const hasCoolerCmd;
	std::unique_ptr<G4UIcmdWith3VectorAndUnit> const rotationCmd, positionCmd;

};

}

}

}

#endif	//	isnp_facility_component_SpallationTargetMessenger_hh
