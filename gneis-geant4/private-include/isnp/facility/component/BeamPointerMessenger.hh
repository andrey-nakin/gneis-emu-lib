#ifndef	isnp_facility_component_BeamPointerMessenger_hh
#define	isnp_facility_component_BeamPointerMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include "isnp/facility/component/BeamPointer.hh"

namespace isnp {

namespace facility {

namespace component {

class BeamPointerMessenger: public G4UImessenger {
public:

	BeamPointerMessenger(BeamPointer& component);
	~BeamPointerMessenger() override;

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	BeamPointer& component;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWith3VectorAndUnit> const rotationCmd, positionCmd;

};

}

}

}

#endif	//	isnp_facility_component_BeamPointerMessenger_hh
