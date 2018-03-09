#ifndef CollimatorC4_hh
#define CollimatorC4_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"

namespace gneis {

namespace facility {

namespace component {

/**
 * Fourth collimator on beams #1 - #5
 */
class CollimatorC4 final : private BoxComponent {
public:

	/**
	 * Disable class instantiation.
	 */
	CollimatorC4() = delete;

	/**
	 * Creates an instance of the lead target.
	 */
	static G4LogicalVolume* AsCylinder(G4double outerRadius);
	static G4LogicalVolume* AsCylinder(const G4String &name,
			G4double outerRadius);

	static G4LogicalVolume* Instance(G4VSolid *outer);
	static G4LogicalVolume* Instance(const G4String &name, G4VSolid *outer);

	static G4String GetDefaultName();

	static G4double GetLength();
	static G4double GetHalfLength();

	static G4double GetDiameter();
	static G4double GetHalfDiameter();

private:

	const static G4double diameter, length;

	static G4LogicalVolume* MakeLogical(G4VSolid *solid);

};

}

}

}

#endif	//	CollimatorC4_hh
