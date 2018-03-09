#ifndef CollimatorC2_hh
#define CollimatorC2_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"

namespace gneis {

namespace facility {

namespace component {

/**
 * Second collimator on beams #1 - #5
 */
class CollimatorC2 final : private BoxComponent {
public:

	/**
	 * Disable class instantiation.
	 */
	CollimatorC2() = delete;

	/**
	 * Creates an instance of the lead target.
	 */
	static G4LogicalVolume* AsCylinder(G4double outerRadius);
	static G4LogicalVolume* AsCylinder(const G4String &name, G4double outerRadius);

	static G4LogicalVolume* Instance(G4VSolid *outer);
	static G4LogicalVolume* Instance(const G4String &name, G4VSolid *outer);

	static G4String GetDefaultName();

	static G4double GetWidth();
	static G4double GetHalfWidth();

	static G4double GetHeight();
	static G4double GetHalfHeight();

	static G4double GetLength();
	static G4double GetHalfLength();

private:

	const static G4double width, height, length;

};

}

}

}

#endif	//	CollimatorC2_hh
