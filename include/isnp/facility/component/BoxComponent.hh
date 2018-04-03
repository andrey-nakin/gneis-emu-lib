#ifndef BoxComponent_hh
#define BoxComponent_hh

#include <G4LogicalVolume.hh>

namespace isnp {

namespace facility {

namespace component {

/**
 * Class encapsulates an information about a box-like component.
 */
class BoxComponent {
protected:

	BoxComponent(BoxComponent const&) = delete;
	BoxComponent& operator=(BoxComponent const&) = delete;

	static G4double HalfOf(G4double v);

	static G4VSolid* MakeCylinder(G4String const &name, G4double len,
			G4double outerRadius);

	static G4VSolid* MakeCylinder(G4String const &name, G4double len,
			G4double outerRadius, G4double aperture);

};

}

}

}

#endif	//	BoxComponent_hh
