#ifndef BoxComponent_hh
#define BoxComponent_hh

#include <G4LogicalVolume.hh>
#include "isnp/util/Box.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Class encapsulates an information about a box-like component.
 */
class BoxComponent {
protected:

	static G4double HalfOf(G4double v);

	static G4VSolid* MakeCylinder(G4String const &name, G4double len,
			G4double outerRadius);

	static G4VSolid* MakeCylinder(G4String const &name, G4double len,
			G4double outerRadius, G4double aperture);

	static G4VSolid* SolidWithAperture(const G4String &name, G4VSolid* outer,
			util::Box const& aperture);

};

}

}

}

#endif	//	BoxComponent_hh
