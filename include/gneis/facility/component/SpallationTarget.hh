#ifndef spallation_target_hh
#define spallation_target_hh

#include <G4LogicalVolume.hh>
#include "BoxComponent.hh"

namespace gneis {

namespace facility {

namespace component {

/**
 * Class encapsulates an information about the lead target
 * used as source of neutrons in the spallation process.
 */
class SpallationTarget final : private BoxComponent {
public:

	/**
	 * Disable class instantiation and assignment.
	 */
	SpallationTarget() = delete;

	/**
	 * Creates an instance of the lead target.
	 */
	static G4LogicalVolume* Instance();
	static G4LogicalVolume* Instance(const G4String &name);

	static G4double GetWidth();
	static G4double GetHeight();
	static G4double GetLength();

	static G4double GetHalfWidth();
	static G4double GetHalfHeight();
	static G4double GetHalfLength();

private:

	const static G4double width, height, length;

};

}

}

}

#endif	//	spallation_target_hh
