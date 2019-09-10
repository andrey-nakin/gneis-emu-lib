#include <G4SystemOfUnits.hh>

#include "isnp/facility/component/CollimatorC4.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

CollimatorC4::CollimatorC4() :
		CylindricComponent(120. * mm, 193. * mm, 875. * mm,
				"G4_STAINLESS-STEEL", repository::Colours::Steel()) {

}

G4String CollimatorC4::GetDefaultName() const {
	return util::NameBuilder::Make("c", "4");
}

}

}

}
