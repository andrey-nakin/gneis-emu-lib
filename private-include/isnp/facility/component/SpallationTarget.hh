#ifndef spallation_target_hh
#define spallation_target_hh

#include <G4Transform3D.hh>
#include <G4LogicalVolume.hh>
#include "BoxComponent.hh"

namespace isnp {

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

	static G4Transform3D GetTransform() {
		return transform;
	}

	static void SetTransform(G4Transform3D const& t) {
		transform = t;
	}

	static void SetTransform(G4Transform3D && t) {
		transform = t;
	}

private:

	const static G4double width, height, length;
	static G4Transform3D transform;

};

}

}

}

#endif	//	spallation_target_hh
