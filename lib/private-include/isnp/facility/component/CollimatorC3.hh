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

	/**
	 * Disable class instantiation.
	 */
	CollimatorC3() = delete;

	/**
	 * Creates an instance of the lead target.
	 */
	static G4LogicalVolume* AsCylinder(G4double outerRadius);
	static G4LogicalVolume* AsCylinder(const G4String &name, G4double outerRadius);

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

#endif	//	CollimatorC3_hh
