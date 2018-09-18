#ifndef CollimatorC4_hh
#define CollimatorC4_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Fourth collimator on beams #1 - #5
 */
class CollimatorC4 final : private BoxComponent {
public:

	CollimatorC4();

	G4LogicalVolume* AsCylinder(G4double outerRadius);
	G4LogicalVolume* AsCylinder(const G4String &name,
			G4double outerRadius);

	G4LogicalVolume* Instance(G4VSolid *outer);
	G4LogicalVolume* Instance(const G4String &name, G4VSolid *outer);

	static G4String GetDefaultName();

	G4double GetLength() const;

	G4double GetInnerDiameter() const{

		return innerDiameter;

	}

private:

	G4double const innerDiameter, outerDiameter, length;

	static G4LogicalVolume* MakeLogical(G4VSolid *solid);

};

}

}

}

#endif	//	CollimatorC4_hh
