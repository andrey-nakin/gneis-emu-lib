#ifndef CollimatorC3_hh
#define CollimatorC3_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Third collimator on beams #1 - #5
 */
class CollimatorC3 final : private BoxComponent {
public:

	CollimatorC3();

	G4LogicalVolume* AsCylinder() const;
	G4LogicalVolume* AsCylinder(const G4String &name) const;

	G4LogicalVolume* Instance(G4VSolid *outer) const;
	G4LogicalVolume* Instance(const G4String &name, G4VSolid *outer) const;

	static G4String GetDefaultName();

	G4double GetInnerDiameter() const {

		return innerDiameter;

	}

	G4double GetInnerRadius() const {

		return GetInnerDiameter() / 2;

	}

	G4double GetOuterDiameter() const {

		return outerDiameter;

	}

	G4double GetOuterRadius() const {

		return GetOuterDiameter() / 2;

	}

	G4double GetLength() const {

		return length;

	}

private:

	G4double const innerDiameter, outerDiameter, length;

	static G4LogicalVolume* MakeLogical(G4VSolid *solid);

};

}

}

}

#endif	//	CollimatorC3_hh
