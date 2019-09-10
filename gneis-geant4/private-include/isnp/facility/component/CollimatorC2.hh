#ifndef CollimatorC2_hh
#define CollimatorC2_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"
#include "isnp/util/Box.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Second collimator on beams #1 - #5
 */
class CollimatorC2 final : private BoxComponent {
public:

	CollimatorC2();

	G4LogicalVolume* AsCylinder(G4double outerRadius) const;
	G4LogicalVolume* AsCylinder(const G4String &name,
			G4double outerRadius) const;

	G4LogicalVolume* Instance(G4VSolid* outer) const;
	G4LogicalVolume* Instance(const G4String &name, G4VSolid* outer) const;

	static G4String GetDefaultName();

	G4double GetLength() const {

		return aperture.GetLength();

	}

private:

	util::Box const aperture;

};

}

}

}

#endif	//	CollimatorC2_hh
