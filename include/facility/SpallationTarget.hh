#ifndef spallation_target_hh
#define spallation_target_hh

#include <G4LogicalVolume.hh>

namespace gneis {

namespace facility {

/**
 * Class encapsulates an information about the lead target
 * used as source of neutrons in the spallation process.
 */
class SpallationTarget final {
public:

	/**
	 * Disable class instantiation and assignment.
	 */
	SpallationTarget() = delete;
	SpallationTarget(SpallationTarget const&) = delete;
	SpallationTarget& operator=(SpallationTarget const&) = delete;

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

	static G4double HalfOf(G4double v);

};

}

}

#endif	//	spallation_target_hh
