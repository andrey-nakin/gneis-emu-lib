#include <G4SystemOfUnits.hh>

#include "isnp/facility/component/CollimatorC3.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

CollimatorC3::CollimatorC3() :
		CylindricComponent(120. * mm, 160. * mm, 600. * mm,
				"G4_STAINLESS-STEEL", repository::Colours::Steel()) {

}

G4String CollimatorC3::GetDefaultName() const {
	return util::NameBuilder::Make("c", "3");
}

}

}

}
