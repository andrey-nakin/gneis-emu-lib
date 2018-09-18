#include <G4SystemOfUnits.hh>

#include "isnp/facility/component/CollimatorC5.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

CollimatorC5::CollimatorC5(G4double const aInnerDiameter) :
		CylindricComponent(aInnerDiameter, 240. * mm, 1000. * mm, "BR05C5S5",
				repository::Colours::Bronze()) {

}

G4String CollimatorC5::GetDefaultName() const {
	return util::NameBuilder::Make("c", "5");
}

}

}

}
