#ifndef CollimatorC1_hh
#define CollimatorC1_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"
#include "isnp/util/Box.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * First collimator on beams #1 - #5
 */
class CollimatorC1 final : private BoxComponent {
public:

	CollimatorC1();

	G4LogicalVolume* AsCylinder(G4double outerRadius) const;
	G4LogicalVolume* AsCylinder(const G4String &name,
			G4double outerRadius) const;

	G4LogicalVolume* Instance(G4VSolid *outer) const;
	G4LogicalVolume* Instance(const G4String &name, G4VSolid *outer) const;

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

#endif	//	CollimatorC1_hh
