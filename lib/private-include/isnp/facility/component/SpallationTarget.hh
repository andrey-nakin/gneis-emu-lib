#ifndef isnp_facility_component_SpallationTarget_hh
#define isnp_facility_component_SpallationTarget_hh

#include <memory>

#include <G4Transform3D.hh>
#include <G4LogicalVolume.hh>
#include "BoxComponent.hh"
#include "isnp/util/Box.hh"

namespace isnp {

namespace facility {

namespace component {

class SpallationTargetMessenger;

/**
 * Class encapsulates an information about the lead target
 * used as source of neutrons in the spallation process.
 */
class SpallationTarget final : private BoxComponent, public util::Box {
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

	G4bool GetHasCooler() const;
	void SetHasCooler(G4bool v);

private:

	std::unique_ptr<SpallationTargetMessenger> const messenger;
	G4double const coolerInnerRadius, coolerOuterRadius, coolerTorusMinRadius;
	G4bool hasCooler;

	static G4Transform3D transform;

};

}

}

}

#endif	//	isnp_facility_component_SpallationTarget_hh
