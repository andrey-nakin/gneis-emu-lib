#ifndef isnp_facility_component_CollimatorC3_hh
#define isnp_facility_component_CollimatorC3_hh

#include "CylindricComponent.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Third collimator on beams #1 - #5
 */
class CollimatorC3 final : public CylindricComponent {
public:

	CollimatorC3();

	G4String GetDefaultName() const override;

};

}

}

}

#endif	//	isnp_facility_component_CollimatorC3_hh
