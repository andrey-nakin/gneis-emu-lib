#ifndef isnp_facility_component_CollimatorC5_hh
#define isnp_facility_component_CollimatorC5_hh

#include "CylindricComponent.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Fiveth collimator on beam #5
 */
class CollimatorC5 final : public CylindricComponent {
public:

	CollimatorC5(G4double innerDiameter);

	G4String GetDefaultName() const override;

};

}

}

}

#endif	//	isnp_facility_component_CollimatorC5_hh
