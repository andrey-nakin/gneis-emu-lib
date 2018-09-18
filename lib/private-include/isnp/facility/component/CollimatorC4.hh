#ifndef isnp_facility_component_CollimatorC4_hh
#define isnp_facility_component_CollimatorC4_hh

#include "CylindricComponent.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Fourth collimator on beams #1 - #5
 */
class CollimatorC4 final : public CylindricComponent {
public:

	CollimatorC4();

	G4String GetDefaultName() const override;

};

}

}

}

#endif	//	isnp_facility_component_CollimatorC4_hh
