#ifndef isnp_facility_component_SpallationTarget_hh
#define spallation_target_hh

#include <G4Transform3D.hh>
#include <G4LogicalVolume.hh>
#include "BoxComponent.hh"
#include "isnp/util/Box.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Class encapsulates an information about the lead target
 * used as source of neutrons in the spallation process.
 */
class SpallationTarget final : private BoxComponent, public util::Box {

	G4LogicalVolume* Instance();
	G4LogicalVolume* Instance(const G4String &name);

public:

	SpallationTarget();

	static G4Transform3D GetTransform() {
		return transform;
	}

	static void SetTransform(G4Transform3D const& t) {
		transform = t;
	}

	static void SetTransform(G4Transform3D && t) {
		transform = t;
	}

	void Place(G4LogicalVolume* destination, G4Transform3D const& transform);

private:

	static G4Transform3D transform;

};

}

}

}

#endif	//	spallation_target_hh
