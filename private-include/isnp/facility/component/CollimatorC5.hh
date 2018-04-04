#ifndef CollimatorC5_hh
#define CollimatorC5_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * First collimator on beams #1 - #5
 */
class CollimatorC5 final : private BoxComponent {
public:

	/**
	 * Disable class instantiation.
	 */
	CollimatorC5() = delete;

	/**
	 * Creates an instance of the lead target.
	 */
	static G4LogicalVolume* AsCylinder(G4double outerRadius, G4double diameter);
	static G4LogicalVolume* AsCylinder(const G4String &name,
			G4double outerRadius, G4double diameter);

	static G4LogicalVolume* Instance(G4VSolid *outer, G4double diameter);
	static G4LogicalVolume* Instance(const G4String &name, G4VSolid *outer,
			G4double diameter);

	static G4String GetDefaultName();

	static G4double GetLength();
	static G4double GetHalfLength();

private:

	const static G4double length;

	static G4LogicalVolume* MakeLogical(G4VSolid *solid);

};

}

}

}

#endif	//	CollimatorC5_hh
