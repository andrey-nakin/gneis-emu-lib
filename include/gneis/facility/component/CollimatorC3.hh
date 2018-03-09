#ifndef CollimatorC3_hh
#define CollimatorC3_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include "BoxComponent.hh"

namespace gneis {

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
	static G4LogicalVolume* Instance(G4VSolid *outer);
	static G4LogicalVolume* Instance(const G4String &name, G4VSolid *outer);

	static G4String GetDefaultName();

	static G4double GetLength();
	static G4double GetHalfLength();

private:

	const static G4double diameter, length;

};

}

}

}

#endif	//	CollimatorC3_hh
